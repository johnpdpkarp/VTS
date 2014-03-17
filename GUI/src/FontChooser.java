/*
 * Copyright (c) Ian F. Darwin, http://www.darwinsys.com/, 1996-2002.
 * All rights reserved. Software written by Ian F. Darwin and others.
 * $Id: FontChooser.java,v 1.1 2007/01/11 20:10:03 badger Exp $
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Java, the Duke mascot, and all variants of Sun's Java "steaming coffee
 * cup" logo are trademarks of Sun Microsystems. Sun's, and James Gosling's,
 * pioneering role in inventing and promulgating (and standardizing) the Java
 * language and environment is gratefully acknowledged.
 *
 * The pioneering role of Dennis Ritchie and Bjarne Stroustrup, of AT&T, for
 * inventing predecessor languages C and C++ is also gratefully acknowledged.
 */

import java.awt.BorderLayout;
import java.awt.Checkbox;
import java.awt.Container;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.Frame;
import java.awt.GraphicsEnvironment;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.colorchooser.*;
import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

/**
 * A font selection dialog.
 * <p>
 * Note: can take a long time to start up on systems with (literally) hundreds
 * of fonts. TODO change list to JList, add a SelectionChangedListener to
 * preview.
 *
 * @author Ian Darwin
 * @version $Id: FontChooser.java,v 1.1 2007/01/11 20:10:03 badger Exp $
 */
public class FontChooser extends JDialog
implements ActionListener, ChangeListener, ItemListener, ListSelectionListener
{
  static final long serialVersionUID = 9;
  // Results:

  /** The font the user has chosen */
  protected Font resultFont;

  /** The resulting font name */
  protected String resultName;

  /** The resulting font size */
  protected int resultSize;

  /** The resulting boldness */
  protected boolean isBold;

  /** The resulting italicness */
  protected boolean isItalic;

  String fontTag = "Font";
  String foreColorTag = "Text Color";
  String backColorTag = "Background Color";
  JColorChooser backChooser = new JColorChooser();
  JColorChooser foreChooser = new JColorChooser();
  JPanel previewPanel;
  csm_gui gui;

  // Working fields

  /** Display text */
  protected String displayText = "Qwerty Yuiop";

  /** The list of Fonts */
  protected String fontList[];

  /** The font name chooser */
  protected JList fontNameChoice;

  /** The font size chooser */
  protected JList fontSizeChoice;

  /** The bold and italic choosers */
  Checkbox bold, italic;

  /** The list of font sizes */
  protected String fontSizes[] = { "8", "10", "11", "12", "14", "16", "18",
      "20", "24", "30", "36", "40", "48", "60", "72" };

  /** The index of the default size (e.g., 14 point == 4) */
  protected static final int DEFAULT_SIZE = 4;

  /**
   * The display area. Use a JLabel as the AWT label doesn't always honor
   * setFont() in a timely fashion :-)
   */
  protected JLabel previewArea;

  /**
   * Construct a FontChooser -- Sets title and gets array of fonts on the
   * system. Builds a GUI to let the user choose one font at one size.
   */
  public FontChooser(csm_gui window, Frame f) {
    super(f, "Font Chooser", true);
    gui = window;

    Container cp = getContentPane();
    JTabbedPane tabPane = new JTabbedPane();
    JPanel fontPanel = createFontPanel();
    previewPanel = new JPanel();
    createChoosers();

    tabPane.addTab(fontTag, fontPanel);
    tabPane.addTab(foreColorTag, foreChooser);
    tabPane.addTab(backColorTag, backChooser);
    cp.add(tabPane, BorderLayout.NORTH);

    foreChooser.getSelectionModel().addChangeListener(this);
    backChooser.getSelectionModel().addChangeListener(this);

    previewArea = new JLabel(displayText, JLabel.CENTER);
    previewArea.setSize(200, 50);
    previewPanel.add(previewArea);
    cp.add(previewPanel, BorderLayout.CENTER);

    JPanel bot = new JPanel();

    JButton okButton = new JButton("Apply");
    bot.add(okButton);
    okButton.addActionListener(this);

    JButton pvButton = new JButton("Preview");
    bot.add(pvButton);
    pvButton.addActionListener(this);

    JButton canButton = new JButton("Cancel");
    bot.add(canButton);
    canButton.addActionListener(this);

    cp.add(bot, BorderLayout.SOUTH);

    previewFont(); // ensure view is up to date!

    //pack();
    setLocation(100, 100);
  }

  protected JPanel createFontPanel()
  {
    JPanel fontPanel = new JPanel(new GridBagLayout());
    GridBagConstraints constraints = new GridBagConstraints();

    //Toolkit toolkit = Toolkit.getDefaultToolkit();
    // For JDK 1.1: returns about 10 names (Serif, SansSerif, etc.)
    // fontList = toolkit.getFontList();
    // For JDK 1.2: a much longer list; most of the names that come
    // with your OS (e.g., Arial), plus the Sun/Java ones (Lucida,
    // Lucida Bright, Lucida Sans...)
    fontList = GraphicsEnvironment.getLocalGraphicsEnvironment()
        .getAvailableFontFamilyNames();

    fontNameChoice = new JList(fontList);
    JScrollPane fontNameArea = new JScrollPane(fontNameChoice);
    fontNameArea.setWheelScrollingEnabled(true);
    fontNameChoice.setSelectedIndex(0);

    fontSizeChoice = new JList(fontSizes);
    JScrollPane fontSizeArea = new JScrollPane(fontSizeChoice);
    fontSizeArea.setWheelScrollingEnabled(true);

    fontSizeChoice.setSelectedIndex(DEFAULT_SIZE);

    JPanel attrs = new JPanel();
    attrs.setLayout(new GridLayout(0, 1));
    attrs.add(bold = new Checkbox("Bold", false));
    attrs.add(italic = new Checkbox("Italic", false));

    constraints.fill = GridBagConstraints.VERTICAL;
    constraints.gridx = 0;
    fontPanel.add(fontNameArea, constraints);
    constraints.fill = GridBagConstraints.NONE;
    constraints.gridx++;
    fontPanel.add(fontSizeArea, constraints);
    constraints.gridx++;
    fontPanel.add(attrs, constraints);

    fontNameChoice.addListSelectionListener(this);
    fontSizeChoice.addListSelectionListener(this);
    bold.addItemListener(this);
    italic.addItemListener(this);

    return fontPanel;
  }

  protected void createChoosers()
  {
      // Retrieve the current set of panels
      AbstractColorChooserPanel[] oldPanels = backChooser.getChooserPanels();

      // Remove panels
      for (int i=0; i<oldPanels.length; i++)
      {
         String clsName = oldPanels[i].getClass().getName();
         if (clsName.equals("javax.swing.colorchooser.DefaultSwatchChooserPanel"))
         {
            // Remove swatch chooser if desired
            //backChooser.removeChooserPanel(oldPanels[i]);
         }
         else if (clsName.equals("javax.swing.colorchooser.DefaultRGBChooserPanel"))
         {
            // Remove rgb chooser if desired
            backChooser.removeChooserPanel(oldPanels[i]);
         }
         else if (clsName.equals("javax.swing.colorchooser.DefaultHSBChooserPanel"))
         {
            // Remove hsb chooser if desired
            backChooser.removeChooserPanel(oldPanels[i]);
         }
      }

      backChooser.setPreviewPanel(new JPanel());

      // Retrieve the current set of panels
      oldPanels = foreChooser.getChooserPanels();

      // Remove panels
      for (int i=0; i<oldPanels.length; i++)
      {
         String clsName = oldPanels[i].getClass().getName();
         if (clsName.equals("javax.swing.colorchooser.DefaultRGBChooserPanel"))
         {
            // Remove rgb chooser if desired
            foreChooser.removeChooserPanel(oldPanels[i]);
         }
         else if (clsName.equals("javax.swing.colorchooser.DefaultHSBChooserPanel"))
         {
            // Remove hsb chooser if desired
            foreChooser.removeChooserPanel(oldPanels[i]);
         }
      }

      foreChooser.setPreviewPanel(new JPanel());
  }

  /**
   * Called from the action handlers to get the font info, build a font, and
   * set it.
   */
  protected void previewFont() {
    resultName = fontNameChoice.getSelectedValue().toString();
    String resultSizeName = fontSizeChoice.getSelectedValue().toString();
    int resultSize = Integer.parseInt(resultSizeName);
    isBold = bold.getState();
    isItalic = italic.getState();
    int attrs = Font.PLAIN;
    if (isBold)
      attrs = Font.BOLD;
    if (isItalic)
      attrs |= Font.ITALIC;
    resultFont = new Font(resultName, attrs, resultSize);
    // System.out.println("resultName = " + resultName + "; " +
    //     "resultFont = " + resultFont);
    previewArea.setFont(resultFont);
    pack(); // ensure Dialog is big enough.
  }

  /** Set the selected font name. */
  public void setSelectedFont(Font font)
  {
	  fontNameChoice.setSelectedValue(font.getFamily(),true);
	  fontSizeChoice.setSelectedValue(String.valueOf(font.getSize()), true);

      bold.setState(font.isBold());
      italic.setState(font.isItalic());
	  previewFont();
  }

  public void setColors(Color backColor, Color foreColor)
  {
	  previewPanel.setBackground(backColor);
	  previewArea.setForeground(foreColor);
	  previewFont();
  }

  /** Retrieve the selected font name. */
  public String getSelectedName() {
    return resultName;
  }

  /** Retrieve the selected size */
  public int getSelectedSize() {
    return resultSize;
  }

  /** Retrieve the selected font, or null */
  public Font getSelectedFont() {
    return resultFont;
  }

  public Color getSelectedBackground()
  {
	return previewPanel.getBackground();
  }

  public Color getSelectedForeground()
  {
	return previewArea.getForeground();
  }

  public void actionPerformed(ActionEvent event)
  {
      String command = event.getActionCommand();

      if(command.equals("Apply"))
      {
         gui.applyFont(resultFont,
                       previewPanel.getBackground(),
                       previewArea.getForeground());
         dispose();
         setVisible(false);
	  }
	  else if(command.equals("Preview"))
	  {
         gui.applyFont(resultFont,
                       previewPanel.getBackground(),
                       previewArea.getForeground());
	  }
	  else if(command.equals("Cancel"))
	  {
         // Set all values to null. Better: restore previous.
         resultFont = null;
         resultName = null;
         resultSize = 0;
         isBold = false;
         isItalic = false;

         dispose();
         setVisible(false);
	  }
  }

  public void stateChanged(ChangeEvent event)
  {
      ColorSelectionModel model = (ColorSelectionModel)event.getSource();

      //----- Get the new color value
      if(model == foreChooser.getSelectionModel())
      {
		  previewArea.setForeground(model.getSelectedColor());
	  }
	  else if(model == backChooser.getSelectionModel())
	  {
		  //previewArea.setBackground(model.getSelectedColor());
		  previewPanel.setBackground(model.getSelectedColor());
	  }
   }

   public void valueChanged(ListSelectionEvent event)
   {
	  Object obj = event.getSource();

	  if(obj == fontNameChoice ||
	     obj == fontSizeChoice)
	  {
		  previewFont();
	  }
   }

   public void itemStateChanged(ItemEvent event)
   {
	  Object obj = event.getSource();

	  if(obj == bold ||
	     obj == italic)
	  {
		  previewFont();
	  }
   }
}
