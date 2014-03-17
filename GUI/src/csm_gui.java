//----- Data IO
import java.io.IOException;
import java.io.File;
import java.io.FileInputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

//----- Basic GUI components
import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.colorchooser.*;
import javax.swing.table.*;
import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;

//----- GUI support classes
import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.awt.event.WindowAdapter;
import java.util.ArrayList;
import java.util.Vector;

//----- XML Classes
import org.w3c.dom.Document;
import org.w3c.dom.*;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.*;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

//////////////////////////////////////////////////////////
//
//  Class: OutputTable
//
//  Description:  Table for the script output
//
//  Author: Robert Badger
//
//  Modification: 04 Jan 2007 (RTB) - Initial Version
//
//////////////////////////////////////////////////////////
class OutputTable extends DefaultTableModel
{
   static final long serialVersionUID = 9;

   int mNumRows;                 //----- Number of table Rows
   int mNumCols;                 //----- Number of table Cols
   ArrayList mData;              //----- Data Array
   ArrayList mErrorRows;         //----- List or Error Row Indexes
   ArrayList mWarnRows;          //----- List or Warning Row Indexes

   //////////////////////////////////////////////////////
   //
   //  Function: Constructor
   //
   //  Description: Initializes the class
   //
   //  Inputs: None
   //
   //  Return: itself
   //
   //  Author: Robert Badger
   //
   //  Modification: 04 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public OutputTable()
   {
      mNumRows = 10;
      mNumCols = 10;
      mData = new ArrayList(mNumRows);
      mErrorRows = new ArrayList();
      mWarnRows = new ArrayList();

      for(int i=0;i<mNumRows;i++)
      {
         mData.add(new ArrayList(mNumCols));

         for(int j=0;j<mNumCols;j++)
            ((ArrayList)mData.get(i)).add("");
      }
   }

   //////////////////////////////////////////////////////
   //
   //  Function: addErrorRow
   //
   //  Description: Add a row to the list of rows with an error
   //
   //  Inputs: int - row to be added to the error list
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 04 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public void addErrorRow(int row)
   {
      mErrorRows.add(new Integer(row));
   }

   //////////////////////////////////////////////////////
   //
   //  Function: addWarningRow
   //
   //  Description: Add a row to the list of rows with a warning
   //
   //  Inputs: int - row to be added to the warning list
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 04 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public void addWarningRow(int row)
   {
      mWarnRows.add(new Integer(row));
   }

   //////////////////////////////////////////////////////
   //
   //  Function: clear
   //
   //  Description: reset the table
   //
   //  Inputs: None
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 04 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public void clear()
   {
      int i;

      for(i=mData.size() - 1;i>=0;i--)
         ((ArrayList)mData.get(i)).clear();
      mData.clear();
      mErrorRows.clear();
      mWarnRows.clear();

      mNumRows = 10;
      mNumCols = 10;

      fireTableStructureChanged();
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getColumnCount
   //
   //  Description: Get the current number of columns
   //
   //  Inputs: None
   //
   //  Return: Number of table columns
   //
   //  Author: Robert Badger
   //
   //  Modification: 04 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public int getColumnCount()
   {
      return mNumCols;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getColumnName
   //
   //  Description: Get the Name of the column
   //
   //  Inputs: int - col number to get the name
   //
   //  Return: Name of the requested column
   //
   //  Author: Robert Badger
   //
   //  Modification: 04 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public String getColumnName(int col)
   {
      String Name = "";

      if(col == 0)
         Name = "Index";
      else if(col % 3 == 1)
         Name = "Return";
      else if(col % 3 == 2)
         Name = "Difference";
      else
         Name = "Pass/Fail";

      return Name;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getRowCount
   //
   //  Description: Get the current number of rows
   //
   //  Inputs: None
   //
   //  Return: Number of table rows
   //
   //  Author: Robert Badger
   //
   //  Modification: 04 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public int getRowCount()
   {
      return mNumRows;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getValueAt
   //
   //  Description: Get the object represented by the requested cell
   //
   //  Inputs: int row - row of requested cell
   //          int col - column of the requested cell
   //
   //  Return: Object at requested cell
   //
   //  Author: Robert Badger
   //
   //  Modification: 04 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public Object getValueAt(int row, int col)
   {
      Object value = "";

      if(row < mData.size() && col < ((ArrayList)mData.get(row)).size())
         value = ((ArrayList)mData.get(row)).get(col);

      return value;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: isCellEditable
   //
   //  Description: Determine if a specified cell is editable
   //
   //  Inputs: int row - row of requested cell
   //          int col - column of the requested cell
   //
   //  Return: True if cell is editable
   //          False if cell is static
   //
   //  Author: Robert Badger
   //
   //  Modification: 04 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public boolean isCellEditable(int row, int col)
   {
      return false;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: isErrorRow
   //
   //  Description: Determine if a row is in the error list
   //
   //  Inputs: int row - row of requested cell
   //
   //  Return: True if row contains an error
   //          False if row has no errors
   //
   //  Author: Robert Badger
   //
   //  Modification: 04 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public boolean isErrorRow(int row)
   {
      return mErrorRows.contains(new Integer(row));
   }

   //////////////////////////////////////////////////////
   //
   //  Function: isWarningRow
   //
   //  Description: Determine if a row is in the warning list
   //
   //  Inputs: int row - row of requested cell
   //
   //  Return: True if row contains an warnings
   //          False if row has no warnings
   //
   //  Author: Robert Badger
   //
   //  Modification: 04 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public boolean isWarningRow(int row)
   {
      return mWarnRows.contains(new Integer(row));
   }

   //////////////////////////////////////////////////////
   //
   //  Function: setValueAt
   //
   //  Description: Set the object represented by the requested cell
   //
   //  Inputs: Object data - object at a requested cell
   //          int row - row of requested cell
   //          int col - column of the requested cell
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 04 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public void setValueAt(Object data, int row, int col)
   {
      int i;                     //----- Loop Variable

      for(i=mData.size();i<=row;i++)
         mData.add(new ArrayList());

      mNumRows = mData.size();

      for(i=((ArrayList)mData.get(row)).size();i<=col;i++)
         ((ArrayList)mData.get(row)).add("");

      if(mNumCols <= col)
      {
         mNumCols = col + 1;
         fireTableStructureChanged();
      }

      ((ArrayList)mData.get(row)).set(col, data);
   }
}

//////////////////////////////////////////////////////////
//
//  Class: OutputRenderer
//
//  Description:  Render a cell for the table
//
//  Author: Robert Badger
//
//  Modification: 04 Jan 2007 (RTB) - Initial Version
//
//////////////////////////////////////////////////////////
class OutputRenderer extends DefaultTableCellRenderer
{
   static final long serialVersionUID = 9;

   //////////////////////////////////////////////////////
   //
   //  Function: getTableCellRendererComponent
   //
   //  Description: Edit a cell render background color
   //
   //  Inputs: JTable table       - Table class
   //          Object object      - Object value
   //          boolean isSelected - is cell selected flag
   //          boolean hasFocus   - does cell have focus
   //          int row            - row of cell
   //          int column         - column of cell
   //
   //  Return: Cell render
   //
   //  Author: Robert Badger
   //
   //  Modification: 04 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public final Component getTableCellRendererComponent (
      JTable table,
      Object object,
      boolean isSelected,
      boolean hasFocus,
      int row,
      int column)
   {
      Component c = super.getTableCellRendererComponent(table,object,isSelected,
         hasFocus,row,column);

      OutputTable model = (OutputTable)table.getModel();

      if (isSelected)
         c.setBackground(table.getSelectionBackground());
      else if (model.isWarningRow(row))
         c.setBackground(Color.YELLOW);
      else if (model.isErrorRow(row))
         c.setBackground(Color.RED);
      else
         c.setBackground(table.getBackground());

      return c;
   }
}

//////////////////////////////////////////////////////////
//
//  Class: csm_gui
//
//  Description:  GUI interfact to the VTS program
//
//  Author: Robert Badger
//
//  Modification: 20 Oct 2006 (RTB) - Initial Version
//
//////////////////////////////////////////////////////////
public class csm_gui extends JPanel
implements ActionListener, ListSelectionListener
{
   static final long serialVersionUID = 9;
   //----- GUI variables
   String mWindowTitle    = "CSM GUI";
   int mVtsHeight         = 500;
   int mInputHeight       = 30;
   int mButtonHeight      = 30;
   int mWindowHeight      = mVtsHeight + mInputHeight + mButtonHeight;
   int mBrowserWidth      = 600;
   int mListWidth         = 150;
   int mWindowWidth       = mBrowserWidth + mListWidth;

   //----- Button and Label Tags
   String mExitTag     = "Exit";
   String mClearTag    = "Clear";
   String mLoadTag     = "Load Script";
   String mFontTag     = "Change Font";
   String mVtsTag      = "Program";
   String mTableTag    = "Table";
   String mInputTag    = "Input Command:";
   String mOutputTag   = "Output:";
   String mPluginTag   = "Plugins:";
   String mModelTag    = "Models:";
   String mSelectorTag = "Output Selector:";

   //----- GUI Components
   JFrame           mFrame;      //----- Main Frame of the GUI
   JComboBox        mOutputList; //----- List of Output Commands
   static JTextArea mBrowserArea;//----- VTS output text
   JScrollPane      mBrowserView;//----- Scroll area for VTS output
   OutputTable      mOutputModel;//----- Table data Model
   JTable           mOutputTable;//----- Output Table
   JTextField       mInputLine;  //----- Input VTS command line
   static JList     mPluginList; //----- List of vts plugins
   JList            mModelList;  //----- List of plugins Models
   JTabbedPane      mTabPane;    //----- Tab Pane
   JLabel           mInputLabel; //----- Input Command Label
   JLabel           mOutputLabel;//----- Output Area Label
   JLabel           mPluginLabel;//----- Plugin List Label
   JLabel           mModelLabel; //----- Plugin List Label
                                 //----- Output Select Label
   JLabel           mSelectorLabel;

   //----- VTS Interface
                                 //----- Write to send text to VTS
   static OutputStreamWriter mToVTS;
                                 //----- Reader to read text from VTS
   static InputStreamReader mFromVTS;
   static String    mOutput = "";//----- Output String from VTS
                                 //----- Last line of VTS output
   static String    mCurrentLine = "";

                                 //----- VTS process
   static Process   mVtsProcess = null;
   static Vector mCommands;      //----- Command of the VTS
   static Vector mPluginNames;   //----- List of VTS plugins
   static Vector mModelNames;    //----- List of plugin Models
   Vector   mOutputs;            //----- List of output from scripts
   vtsConfig        mVTSConfig;  //----- Values from the config file

   //////////////////////////////////////////////////////
   //
   //  Function: Constructor
   //
   //  Description: Initializes the class
   //
   //  Inputs: None
   //
   //  Return: itself
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 OCT 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public csm_gui()
   {
      GridBagLayout contlayout=new GridBagLayout();
      GridBagConstraints constraint=new GridBagConstraints();

      mVTSConfig = new vtsConfig();
      mVTSConfig.loadConfigFile("config.xml");

      //----- Define the Main Window
      mFrame = new JFrame(mWindowTitle);
      mFrame.addWindowListener(new ExitListener(mVtsProcess));
      Container content = mFrame.getContentPane();

      WindowUtilities.setNativeLookAndFeel();

      //----- Create Output Selector
      mSelectorLabel = new JLabel(mSelectorTag);
      mOutputList = new JComboBox();
      mOutputList.addItem("Standard Output");
      mOutputList.addActionListener(this);

      //----- Create VTS Panel
      JPanel vtsPane = createVtsPane();

      //----- Create Output Table
      mOutputModel = new OutputTable();
      mOutputTable = new JTable(mOutputModel);
      JScrollPane scrollPane = new JScrollPane(mOutputTable);
      mOutputTable.setPreferredScrollableViewportSize(
         new Dimension( mWindowWidth + 10, mVtsHeight+10 ));
      mOutputTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
      mOutputTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
      mOutputTable.setDefaultRenderer(new Object().getClass(),
         new OutputRenderer());

      mOutputTable.getSelectionModel().addListSelectionListener(this);

      //----- Create Tab Panel
      mTabPane = new JTabbedPane();
      mTabPane.addTab(mVtsTag, vtsPane);
      mTabPane.addTab(mTableTag, scrollPane);

      //----- Add Button at Bottom
      JPanel buttonPane = createButtonPane();

      //----- Assign components to proper panels
      content.setLayout(contlayout);
      constraint.fill = GridBagConstraints.BOTH;
      constraint.gridx = 0;
      constraint.gridy = 0;
      constraint.gridwidth = 1;
      constraint.weightx = 0;
      constraint.weighty = 0;
      content.add(mSelectorLabel, constraint);
      constraint.gridx++;
      constraint.weightx = 1;
      content.add(mOutputList, constraint);
      constraint.gridx = 0;
      constraint.gridy++;
      constraint.gridwidth = 2;
      constraint.weighty = 1;
      content.add(mTabPane,    constraint);
      constraint.gridy++;
      constraint.weighty = 0;
      content.add(buttonPane,  constraint);

      //----- Initial Window Values
      mFrame.setSize(mWindowWidth + 10, mWindowHeight + 20);
      mFrame.setVisible(true);
      //mCommands    = new Vector<String>();
      //mPluginNames = new Vector<String>();
      //mOutputs     = new Vector<String>();
      mCommands    = new Vector();
      mPluginNames = new Vector();
      mModelNames  = new Vector();
      mOutputs     = new Vector();

      int attrs = Font.PLAIN;
      if(mVTSConfig.getFontBold())
         attrs = Font.BOLD;
      if(mVTSConfig.getFontItalic())
         attrs |= Font.ITALIC;

      if(mVTSConfig.getFontName() != "" &&
         mVTSConfig.getFontSize() != 0)
      {
         Font myOldFont = new Font(mVTSConfig.getFontName(), attrs,
            mVTSConfig.getFontSize());

         applyFont(myOldFont, mVTSConfig.getBackColor(),
            mVTSConfig.getTextColor());
      }
   }

   //////////////////////////////////////////////////////
   //
   //  Function: createVtsPane
   //
   //  Description: Create the vts output Pane
   //
   //  Inputs: None
   //
   //  Return: JPanel = the vts Pane
   //
   //  Author: Robert Badger
   //
   //  Modification: 27 NOV 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public JPanel createVtsPane()
   {
      GridBagLayout vtsLayout;   //----- Panel Layout variable
                                 //----- Constraints on Panel
      GridBagConstraints vtsConstraint;
                                 //----- Panel to be created
      JPanel vtsPane = new JPanel();

      //----- Initialize Variables
      vtsLayout=new GridBagLayout();
      vtsConstraint=new GridBagConstraints();
      vtsPane = new JPanel();

      JPanel outputPane = new JPanel();

      //----- Create Output Screen
      mBrowserArea = new JTextArea(0, 30);
      mBrowserArea.setEditable(false);
      mBrowserArea.setBackground(Color.white);

      mBrowserView = new JScrollPane(mBrowserArea);
      mBrowserView.setPreferredSize(
         new Dimension( mBrowserWidth, mVtsHeight ));
      mBrowserView.setWheelScrollingEnabled(true);

      mOutputLabel = new JLabel(mOutputTag);
      outputPane.setLayout(new BorderLayout());
      outputPane.add(mOutputLabel, BorderLayout.NORTH);
      outputPane.add(mBrowserView, BorderLayout.CENTER);

      //----- Create Plugin List
      JPanel pluginPane = new JPanel();
      mPluginList = new JList();
      mPluginList.setPreferredSize(
         new Dimension( mListWidth, mVtsHeight/2 ));
      mModelList = new JList();
      mModelList.setPreferredSize(
         new Dimension( mListWidth, mVtsHeight/2 ));

      mPluginLabel = new JLabel(mPluginTag);
      mModelLabel  = new JLabel(mModelTag);
      pluginPane.setLayout(vtsLayout);
      vtsConstraint.fill = GridBagConstraints.BOTH;
      vtsConstraint.gridx = 0;
      vtsConstraint.gridy = 0;
      vtsConstraint.gridwidth = 1;
      vtsConstraint.weightx = 1;
      vtsConstraint.weighty = 0;
      pluginPane.add(mPluginLabel, vtsConstraint);
      vtsConstraint.gridy++;
      vtsConstraint.weighty = 1;
      pluginPane.add(mPluginList,  vtsConstraint);
      vtsConstraint.gridy++;
      vtsConstraint.weighty = 0;
      pluginPane.add(mModelLabel,  vtsConstraint);
      vtsConstraint.gridy++;
      vtsConstraint.weighty = 1;
      pluginPane.add(mModelList,   vtsConstraint);
      mPluginList.addListSelectionListener(this);

      //----- Build split-pane view
      JSplitPane splitPane = new JSplitPane(
         JSplitPane.HORIZONTAL_SPLIT,
         outputPane,
         pluginPane );
      splitPane.setContinuousLayout( true );
      splitPane.setDividerLocation( mBrowserWidth );
      splitPane.setPreferredSize( new Dimension( mWindowWidth + 10, mVtsHeight+10 ));

      //----- Add Input Command Line
      mInputLabel = new JLabel(mInputTag);
      mInputLine = new JTextField();
      mInputLine.setPreferredSize(new Dimension(mWindowWidth, mInputHeight));
      mInputLine.setBackground(Color.white);
      mInputLine.addActionListener(this);

      //----- Assign components to proper panels
      vtsPane.setLayout(vtsLayout);
      vtsConstraint.fill = GridBagConstraints.BOTH;
      vtsConstraint.gridx = 0;
      vtsConstraint.gridy = 0;
      vtsConstraint.gridwidth = 2;
      vtsConstraint.weightx = 1;
      vtsConstraint.weighty = 1;
      vtsPane.add(splitPane,  vtsConstraint);
      vtsConstraint.gridwidth = 1;
      vtsConstraint.gridy++;
      vtsConstraint.weightx = 0;
      vtsConstraint.weighty = 0;
      vtsPane.add(mInputLabel, vtsConstraint);
      vtsConstraint.gridx++;
      vtsConstraint.weightx = 1;
      vtsPane.add(mInputLine, vtsConstraint);

      return vtsPane;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: createButtonPane
   //
   //  Description: Create the button Pane
   //
   //  Inputs: None
   //
   //  Return: JPanel = the button Pane
   //
   //  Author: Robert Badger
   //
   //  Modification: 27 NOV 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   private JPanel createButtonPane()
   {
                                 //----- Panel
      JPanel buttonArea = new JPanel();

      buttonArea.setPreferredSize(new Dimension(mWindowWidth, mButtonHeight));

      JButton exitButton  = new JButton(mExitTag);
      JButton clearButton = new JButton(mClearTag);
      JButton loadButton  = new JButton(mLoadTag);
      JButton fontButton  = new JButton(mFontTag);

      exitButton.addActionListener(this);
      clearButton.addActionListener(this);
      loadButton.addActionListener(this);
      fontButton.addActionListener(this);

      buttonArea.add(exitButton);
      buttonArea.add(clearButton);
      buttonArea.add(loadButton);
      buttonArea.add(fontButton);

      return buttonArea;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: applyFont
   //
   //  Description: Set new font and colors for the GUI
   //
   //  Inputs: myNewFont - new font
   //          backColor - new background color
   //          foreColor - new text color
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 11 JAN 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public void applyFont(Font myNewFont, Color backColor, Color foreColor)
   {
	  mBrowserArea.setFont(myNewFont);
      mInputLine.setFont(myNewFont);
      mOutputList.setFont(myNewFont);
      mPluginList.setFont(myNewFont);
      mModelList.setFont(myNewFont);
      mInputLabel.setFont(myNewFont);
      mOutputLabel.setFont(myNewFont);
      mPluginLabel.setFont(myNewFont);
      mModelLabel.setFont(myNewFont);
      mSelectorLabel.setFont(myNewFont);
      mOutputTable.setFont(myNewFont);
      mTabPane.setFont(myNewFont);
      JTableHeader header = mOutputTable.getTableHeader();
      header.setFont(myNewFont);

      mBrowserArea.setBackground(backColor);
      mInputLine.setBackground(backColor);
      mOutputList.setBackground(backColor);
      mPluginList.setBackground(backColor);
      mModelList.setBackground(backColor);

      mBrowserArea.setForeground(foreColor);
      mInputLine.setForeground(foreColor);
      mOutputList.setForeground(foreColor);
      mPluginList.setForeground(foreColor);
      mModelList.setForeground(foreColor);

      mFrame.pack();

      //----- Write A new Config File
      mVTSConfig.setFontBold(myNewFont.isBold());
      mVTSConfig.setFontItalic(myNewFont.isItalic());
      mVTSConfig.setFontName(myNewFont.getName());
      mVTSConfig.setFontSize(myNewFont.getSize());
      mVTSConfig.setBackColor(backColor);
      mVTSConfig.setTextColor(foreColor);

      mVTSConfig.writeConfigFile("config.xml");
   }

   //////////////////////////////////////////////////////
   //
   //  Function: isCommand
   //
   //  Description: Determine if a data line is a command
   //
   //  Inputs: instruction - data line to check if it is a command
   //
   //  Return: boolean show if line is a command string
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 OCT 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public boolean isCommand(String instruction)
   {
      boolean foundFlag = false; //----- Command found Flag
      int i;                     //----- Loop Variable

      for(i=0;i<mCommands.size() && foundFlag == false;i++)
         if(instruction.trim().startsWith(mCommands.get(i).toString()))
            foundFlag = true;

      return foundFlag;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: resetOutputList
   //
   //  Description: Clear the command line output
   //
   //  Inputs: None
   //
   //  Return: None
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 OCT 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public void resetOutputList()
   {
      mOutputList.removeAllItems();
      mOutputs.clear();
      mOutputList.addItem("Standard Output");
      mOutputModel.clear();
   }

   //////////////////////////////////////////////////////
   //
   //  Function: addTableRow
   //
   //  Description: Add a string to a Table
   //
   //  Inputs: row - Table row to Insert data
   //          index - Command Index
   //          line  - String of data
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 22 Nov 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public void addTableRow(int row, int index, String line)
   {
      int beginIndex = 0;        //----- Starting Index
      int endIndex = 0;          //----- EndIndex Index
      int col = 0;               //----- Table Column
      String outStr;             //----- Output String

      mOutputModel.setValueAt(String.valueOf(index), row, col++);

      endIndex = line.indexOf(" ", beginIndex);
      while(endIndex != -1)
      {
         outStr = line.substring(beginIndex, endIndex);
         if(outStr.trim().length() > 0)
            mOutputModel.setValueAt(outStr, row, col++);

         beginIndex = endIndex + 1;
         endIndex = line.indexOf(" ", beginIndex);
      }

      outStr = line.substring(beginIndex);

      if(outStr.trim().length() > 0)
         mOutputModel.setValueAt(outStr, row, col);
   }

   //////////////////////////////////////////////////////
   //
   //  Function: runScriptFile
   //
   //  Description: Load and run a script file through vts
   //
   //  Inputs: File to be processed
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 OCT 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public void runScriptFile(File scriptFile)
   {
      FileInputStream fin;       //----- Stream to read file
      BufferedReader buff;       //----- Stream to read file
      String line;               //----- Script command line
      String cmdLine;            //----- Last command line
      String output;             //----- Output from VTS process
      String outputLine;         //----- Output data line
      int index;                 //----- Index of the command
      int row;                   //----- Row of the table row
      int outputIndex;           //----- Index of output Line
      int outputLength;          //----- Length of output Line
      boolean foundCommandFlag;  //----- Found the first command

      //----- Initialize variables
      foundCommandFlag = false;
      cmdLine = "";
      index = 1;
      row = 0;
      resetOutputList();

      try
      {
         //----- Open an input stream
         fin = new FileInputStream(scriptFile);
         buff = new BufferedReader(new InputStreamReader(fin));

         while((line = buff.readLine()) != null)
         {
            //----- Capture the exit command and us it as an exit
            if(!line.toLowerCase().startsWith("exit"))
            {
               //----- Determine if the line is a VTS command
               if(isCommand(line))
               {
                  //----- Execute previous command when next is found
                  if(foundCommandFlag)
                  {
                     mToVTS.flush();

                     output = getBufferOutput();
                     System.out.println(output);

                     outputIndex = output.indexOf("Output Results:");
                     if(outputIndex != -1)
                     {
                        outputIndex += 17;
                        outputLength = output.indexOf("\n", outputIndex + 1);
                        outputLine = output.substring(outputIndex, outputLength);

                        if(output.length() > outputLength + 1)
                        {
                           if(output.charAt(outputLength + 1) == 'E')
                              mOutputModel.addErrorRow(row);
                           if(output.charAt(outputLength + 1) == 'W')
                              mOutputModel.addWarningRow(row);
                        }

                        addTableRow(row++, index, outputLine);
                     }

                     mOutputs.add(output);

                     mOutputList.addItem(String.valueOf(index++) + ". " + cmdLine);
                  }

                  foundCommandFlag = true;
                  cmdLine = line;
               }

               //----- Send current line to vts
               System.out.println(line);
               if(!line.toLowerCase().endsWith(".csv"))
                  mToVTS.write(line + "\n");
            }
            else
            {
               break;
            }
         }

         //----- Process remaining script data
         mToVTS.flush();

         output = getBufferOutput();

         mOutputs.add(output);

         mOutputList.addItem(String.valueOf(index++) + ". " + cmdLine);

         //----- Close our input stream
         fin.close();
      }
      //----- Catches any error conditions
      catch (IOException e)
      {
         System.out.println(e.getMessage());
         //e.printStackTrace();
         System.err.println ("Unable to read from file");
      }
   }

   //////////////////////////////////////////////////////
   //
   //  Function: parseCommands
   //
   //  Description: File the help output to determine
   //               commands
   //
   //  Inputs: commands - the output of the help command in vts
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 OCT 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public static void parseCommands(String commands)
   {
      String line;               //----- Line of the help command
      int index = -1;            //----- Index of the end of the command

      index = commands.indexOf('#');
      if(index > 0)
         commands = commands.substring(index - 1);
      index = commands.indexOf('\n');

      while(index != -1)
      {
         line = commands.substring(0, index).trim();

         if(!line.equals("") &&
            !line.equals("#") &&
            !line.startsWith("The following"))
         {
            mCommands.add(line);
         }

         commands = commands.substring(index + 1);
         index = commands.indexOf('\n');
      }
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getInputCommands
   //
   //  Description: Get a list of command from vts
   //
   //  Inputs: None
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 OCT 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public static void getInputCommands()
   {
      String commands;           //----- Output String

      try
      {
         mToVTS.write("help\n");
         mToVTS.flush();
         commands = getBufferOutput();

         parseCommands(commands);
      }
      catch (IOException ioe)
      {
         //----- I/O error
         ioe.printStackTrace();
      }
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getPluginNames
   //
   //  Description: Get a list of the availible plugins
   //
   //  Inputs: None
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 OCT 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public static void getPluginNames()
   {
      String list;               //----- Output String
      String line;               //----- Line of the output
      int index;                 //----- String Index

      try
      {
         mToVTS.write("printList\n");
         mToVTS.flush();
         list = getBufferOutput();

         index = list.indexOf('\n');
         while(index != -1)
         {
            line = list.substring(0, index);
            list = list.substring(index +1);

            if(line.startsWith("Sensor: ") ||
               line.startsWith("Target: "))
            {
               mPluginNames.add(line.substring(8));
            }

            index = list.indexOf('\n');

            mPluginList.setListData(mPluginNames);
         }
      }
      catch (IOException ioe)
      {
         //----- I/O error
         ioe.printStackTrace();
      }
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getOutput
   //
   //  Description: Process the output to the main screen
   //
   //  Inputs: None
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 OCT 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public static void getOutput()
   {
      int c;                     //----- data character from VTS
      String output = "";        //----- Output data line from VTS
                                 //----- Command Prompt found
      boolean newCommandFlag = false;

      try
      {
         while((c = mFromVTS.read()) != -1)
         {
            output += (char)c;

            if(c == '\n' || c == '>')
            {
               mBrowserArea.append(output);
               mBrowserArea.setCaretPosition(mBrowserArea.getDocument().getLength());
               mCurrentLine = output;

               if(!output.equals("vts>"))
               {
                  mOutput += output;
                  output = "";
               }
            }

            newCommandFlag = output.equals("vts> ");

            if(newCommandFlag)
            {
               mOutput += output;
               output = "";
               if(!mFromVTS.ready())
                  break;
            }
         }
      }
      catch (IOException ioe)
      {
         //----- I/O error
         ioe.printStackTrace();
      }
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getBufferOutput
   //
   //  Description: Process the vts output and write it
   //               to a buffer
   //
   //  Inputs: None
   //
   //  Return: String - containing output of command
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 OCT 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public static String getBufferOutput()
   {
      int c;                     //----- data character from VTS
      String output = "";        //----- Output line from VTS
      String buffer = "";        //----- Output data from VTS
                                 //----- Command Prompt found
      boolean newCommandFlag = false;

      try
      {
         while((c = mFromVTS.read()) != -1)
         {
            output += (char)c;

            if(c == '\n' || c == '>')
            {
               buffer += output;

               if(!output.equals("vts>"))
                  output = "";
            }

            newCommandFlag = output.equals("vts> ");

            if(newCommandFlag)
            {
               output = "";
               if(!mFromVTS.ready())
                  break;
            }
         }
      }
      catch (IOException ioe)
      {
         //----- I/O error
         ioe.printStackTrace();
      }

      return buffer;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: actionPerformed
   //
   //  Description: Process the GUI events
   //
   //  Inputs: event - GUI event
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 OCT 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public void actionPerformed(ActionEvent event)
   {
                                 //----- Name of GUI item
      String command = event.getActionCommand();
                                 //----- GUI object
      Object object = event.getSource();
      int index;                 //----- Index variable


      try
      {
         if(command.equals(mExitTag))
         {
            mToVTS.write("Exit\n");
            mToVTS.flush();
            System.exit(0);
         }
         else if(command.equals(mClearTag))
         {
            mOutput = mCurrentLine;
            mBrowserArea.setText(mOutput);

            resetOutputList();
            mOutputList.setSelectedIndex(0);
         }
         else if(command.equals(mLoadTag))
         {
            JFileChooser chooser = new JFileChooser();
            chooser.setCurrentDirectory(new File("./"));
            chooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
            //chooser.setFileFilter(new AllFileFilter());
            int returnVal = chooser.showOpenDialog(csm_gui.this);
            if(returnVal == JFileChooser.APPROVE_OPTION)
            {
               runScriptFile(chooser.getSelectedFile());

               if(mOutputList.getItemCount() > 1)
                  mOutputList.setSelectedIndex(1);
            }
         }
         else if(command.equals(mFontTag))
         {
            FontChooser fc = new FontChooser(this, mFrame);
            fc.setSelectedFont(mBrowserArea.getFont());
            fc.setColors(mBrowserArea.getBackground(),
                         mBrowserArea.getForeground());

            fc.setVisible(true);
         }
         else if(object == mInputLine)
         {
            mToVTS.write(mInputLine.getText() + "\n");
            mToVTS.flush();
            mOutputList.setSelectedIndex(0);
            mBrowserArea.setText(mOutput);

            getOutput();

            if(mInputLine.getText().toLowerCase().equals("exit"))
               System.exit(0);

            mInputLine.setText(null);
         }
         else if(object == mOutputList)
         {
            int i;               //----- Loop Variable
            int rowIndex;        //----- Row Output Index
            //boolean foundIndexFlag = false; //----- Found Row Index Flag
            String value;        //----- Row Index String

            index = mOutputList.getSelectedIndex();
            if(index > 0 && index <= mOutputs.size())
            {
               String output = mOutputs.get(index - 1).toString();

               for(i=0;i<mOutputTable.getRowCount();i++)
               {
                  value = mOutputTable.getValueAt(i, 0).toString();
                  if(!value.equals(""))
                     rowIndex = Integer.parseInt(value);
                  else
                     rowIndex = -1;
                  if(rowIndex == index)
                  {
                     mOutputTable.setRowSelectionInterval(i, i);
                     mOutputTable.scrollRectToVisible(
                        mOutputTable.getCellRect(i, 0, true));
                     //foundIndexFlag = true;
                  }

                  if(rowIndex >= index)
                     break;
               }

               if(output != null)
               {
                  mBrowserArea.setText(output);
               }
            }
            else if(index == 0)
               mBrowserArea.setText(mOutput);
         }
      }
      catch (IOException ioe)
      {
         //----- I/O error
         System.out.println(ioe.getMessage());
         //ioe.printStackTrace();
      }
   }

   //////////////////////////////////////////////////////
   //
   //  Function: valueChanged
   //
   //  Description: List selection Listener
   //
   //  Inputs: event - event of a list being selected
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 28 NOV 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public void valueChanged(ListSelectionEvent event)
   {
      String value;              //----- Selected output value
      int selectedIndex;         //----- Selected Output Index

      //----- Ignore extra messages.
      if (event.getValueIsAdjusting()) return;

      if(event.getSource() == mPluginList)
      {
         String list;             //----- Output of list command
         String line;             //----- line of output data
         int index;               //----- Index of end of line

         try
         {
            mToVTS.write("printModelList " +
                         mPluginList.getSelectedValue().toString() +
                         "\n");
            mToVTS.flush();
            list = getBufferOutput();

            mModelNames.clear();

            index = list.indexOf('\n');
            while(index != -1)
            {
               line = list.substring(0, index);
               list = list.substring(index + 1);

               if(line.length() > 1 &&
                  line.startsWith("\t"))
               {
                  mModelNames.add(line.substring(1));
               }

               index = list.indexOf('\n');

               mModelList.setListData(mModelNames);
            }
         }
         catch (IOException ioe)
         {
            //----- I/O error
            System.out.println(ioe.getMessage());
            //ioe.printStackTrace();
         }
      }
      else
      {
         ListSelectionModel lsm = (ListSelectionModel)event.getSource();
         if (!lsm.isSelectionEmpty())
         {
            value = mOutputTable.getValueAt(
               lsm.getMinSelectionIndex(), 0).toString();
            if(!value.equals(""))
            {
               selectedIndex = Integer.parseInt(value);
               mOutputList.setSelectedIndex(selectedIndex);
            }
         }
      }
   }

   //////////////////////////////////////////////////////
   //
   //  Function: main
   //
   //  Description: Main routine
   //
   //  Inputs: args - command line arguments
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 OCT 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public static void main(String[] args)
   {
      try
      {
         mVtsProcess = Runtime.getRuntime().exec("vts");

         new csm_gui();

         mFromVTS = new InputStreamReader(mVtsProcess.getInputStream());

         mToVTS = new OutputStreamWriter(mVtsProcess.getOutputStream());

         mToVTS.write("out.csv\n");
         mToVTS.flush();
      }
      catch (IOException ioe)
      {
         //----- I/O error
         ioe.printStackTrace();
      }

      getOutput();

      getInputCommands();

      getPluginNames();
   }
}


//////////////////////////////////////////////////////////
//
//  Class: ExitListener
//
//  Description:  Window listener for GUI
//
//  Author: Robert Badger
//
//  Modification: 20 Oct 2006 (RTB) - Initial Version
//
//////////////////////////////////////////////////////////
class ExitListener extends WindowAdapter
{
                                 //----- VTS Process
   static Process mVtsProcess = null;

   //////////////////////////////////////////////////////
   //
   //  Function: Constructor
   //
   //  Description: Initialize the class
   //
   //  Inputs: p - Process GUI is interfacing
   //
   //  Return: itself
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 OCT 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public ExitListener(Process p)
   {
      mVtsProcess = p;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: windowClosing
   //
   //  Description: GUI is closing event
   //
   //  Inputs: event - Window event
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 OCT 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public void windowClosing(WindowEvent event)
   {
      if(mVtsProcess != null)
         mVtsProcess.destroy();

      System.exit(0);
   }
}
