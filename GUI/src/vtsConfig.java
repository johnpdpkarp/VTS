
//----- Java I/O classes
import java.io.*;
import java.net.*;


//----- GUI support classes
import java.awt.Color;

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
//  Class: vtsConfig
//
//  Description:  Run the Update of the podcast
//
//  Author: Robert Badger
//
//  Modification: 20 Feb 2007 (RTB) - Initial Version
//
//////////////////////////////////////////////////////////
class vtsConfig
{
   String  mFontName;                            //----- Name of selected Font
   int     mFontSize;                            //----- Size of Selected Font
   boolean mFontBold;                            //----- Is Font Bold
   boolean mFontItalic;                          //----- Is Font Italic
   Color   mBackColor;                           //----- Background Color
   Color   mTextColor;                           //----- Text Color

   //----- XML Tag Values
   String  mPrefTag      = "Preferences";        //----- Tag for Preferences
   String  mFontNameTag  = "FontName";           //----- Tag for the Font Name
   String  mFontSizeTag  = "FontSize";           //----- Tag for the Font Size
   String  mFontBoldTag  = "FontBold";           //----- Tag for the Font Bold
   String  mFontItalicTag= "FontItalic";         //----- Tag for the Font Italic
   String  mBackColorTag = "BackgroundColor";    //----- Tag for Background Color
   String  mTextColorTag = "TextColor";          //----- Tag for Text Color
   String  mMenuTag      = "Menu";               //----- Tag for Preferences

   String  mInitFontValue = "";                  //----- Initial Font Name
   int     mInitFontSize  = 0;                   //----- Initial Font Size

   //////////////////////////////////////////////////////
   //
   //  Function: Constructor
   //
   //  Description: Initializes the class
   //
   //  Inputs: none
   //
   //  Return: itself
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public vtsConfig()
   {
	   mFontName   = mInitFontValue;
	   mFontSize   = mInitFontSize;
	   mFontBold   = false;
	   mFontItalic = false;
	   mBackColor  = Color.WHITE;
	   mTextColor  = Color.BLACK;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getBackColor
   //
   //  Description: Get the Background color
   //
   //  Inputs: Nothing
   //
   //  Return: Color
   //
   //  Author: Robert Badger
   //
   //  Modification: 22 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   Color getBackColor()
   {
      return mBackColor;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getTextColor
   //
   //  Description: Get the Foreground color
   //
   //  Inputs: Nothing
   //
   //  Return: Color
   //
   //  Author: Robert Badger
   //
   //  Modification: 22 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   Color getTextColor()
   {
      return mTextColor;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getFontName
   //
   //  Description: Get the Name of the selected Font
   //
   //  Inputs: Nothing
   //
   //  Return: String of the name of the font
   //
   //  Author: Robert Badger
   //
   //  Modification: 22 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   String getFontName()
   {
      return mFontName;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getFontBold
   //
   //  Description: Get the Bold flag of the selected Font
   //
   //  Inputs: Nothing
   //
   //  Return: boolean indicaticing if it is a bold font
   //
   //  Author: Robert Badger
   //
   //  Modification: 22 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   boolean getFontBold()
   {
      return mFontBold;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getFontItalic
   //
   //  Description: Get the Italic Flag of the selected Font
   //
   //  Inputs: Nothing
   //
   //  Return: boolean indicaticing if it is an italic font
   //
   //  Author: Robert Badger
   //
   //  Modification: 22 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   boolean getFontItalic()
   {
      return mFontItalic;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: getFontSize
   //
   //  Description: Get the Size of the selected Font
   //
   //  Inputs: Nothing
   //
   //  Return: integer of the string size
   //
   //  Author: Robert Badger
   //
   //  Modification: 22 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   int getFontSize()
   {
      return mFontSize;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: loadPreferences
   //
   //  Description: Load the Prefercences Data from an xml file
   //
   //  Inputs: rootNode - prefercenes node
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   void loadPreferences(Node rootNode)
   {
      Node currentNode;                              //----- Current Node
      String   nodeName;                             //----- Name of the current Node

      currentNode = rootNode.getFirstChild();

      while(currentNode != null)
      {
		 nodeName = currentNode.getNodeName();

         if(nodeName.equals(mFontBoldTag))
		 {
		 	 mFontBold = currentNode.getFirstChild().getNodeValue()
		 	               .equals("true");
		 }
		 else if(nodeName.equals(mFontItalicTag))
		 {
			 mFontItalic = currentNode.getFirstChild().getNodeValue()
			                  .equals("true");
		 }
		 else if(nodeName.equals(mFontNameTag))
		 {
			 mFontName = currentNode.getFirstChild().getNodeValue();
		 }
		 else if(nodeName.equals(mFontSizeTag))
		 {
			 mFontSize = Integer.parseInt(
                currentNode.getFirstChild().getNodeValue());
		 }
		 else if(nodeName.equals(mBackColorTag))
		 {
			 mBackColor = new Color(Integer.parseInt(
                currentNode.getFirstChild().getNodeValue()));
		 }
		 else if(nodeName.equals(mTextColorTag))
		 {
			 mTextColor = new Color(Integer.parseInt(
                currentNode.getFirstChild().getNodeValue()));
		 }

         currentNode = currentNode.getNextSibling();
	  }
   }

   //////////////////////////////////////////////////////
   //
   //  Function: loadMenu
   //
   //  Description: Load the Menu Data from an xml file
   //
   //  Inputs: rootNode - menu node
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   void loadMenu(Node rootNode)
   {
      Node currentNode;                      //----- Current Node
      String   nodeName;                     //----- Name of the current Node

      currentNode = rootNode.getFirstChild();

      while(currentNode != null)
      {
         currentNode = currentNode.getNextSibling();
	  }
   }

   //////////////////////////////////////////////////////
   //
   //  Function: loadConfigFile
   //
   //  Description: Load the Data from an xml file
   //
   //  Inputs: xmlString - name of the configuration file
   //
   //  Return: Vector of RSSData read from the specified file
   //
   //  Author: Robert Badger
   //
   //  Modification: 27 Aug 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public void loadConfigFile(String xmlString)
   {
      DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
      Node     currentNode;                              //----- Current Node
      String   nodeName;                                 //----- Name of the current Node

      if(new File(xmlString).exists())
      {
         try {
            DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
            Document doc = docBuilder.parse(new File(xmlString));

            doc.getDocumentElement().normalize();

            currentNode = doc.getFirstChild().getFirstChild();

            while(currentNode != null)
            {
               nodeName = currentNode.getNodeName();

               if( nodeName.equals(mPrefTag) )
               {
				   loadPreferences(currentNode);
               }
               else if( nodeName.equals(mMenuTag) )
               {
				   loadMenu(currentNode);
               }

               currentNode = currentNode.getNextSibling();
            }
         } catch (SAXException sxe) {
             //----- Error generated during parsing
             Exception  x = sxe;

             if (sxe.getException() != null)
                x = sxe.getException();
             x.printStackTrace();
         } catch (ParserConfigurationException pce) {
             //----- Parser with specified options can't be built
             pce.printStackTrace();
         } catch(IOException ioe) {
             //----- I/O error
             ioe.printStackTrace();
         }
      }
   	  else
   	  {
   		 System.out.println("Config file "+ xmlString + " not found.");
   	  }
   }

   //////////////////////////////////////////////////////
   //
   //  Function: setBackColor
   //
   //  Description: Set the Background color
   //
   //  Inputs: Color
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 22 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   void setBackColor(Color value)
   {
      mBackColor = value;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: setTextColor
   //
   //  Description: Set the Foreground color
   //
   //  Inputs: Color
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 22 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   void setTextColor(Color value)
   {
      mTextColor = value;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: setFontBold
   //
   //  Description: Set the Bold flag of the selected Font
   //
   //  Inputs: boolean of the Bold Flag
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 22 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   void setFontBold(boolean value)
   {
      mFontBold = value;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: setFontItalic
   //
   //  Description: Set the Italic flag of the selected Font
   //
   //  Inputs: boolean of the Italic Flag
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 22 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   void setFontItalic(boolean value)
   {
      mFontItalic = value;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: setFontName
   //
   //  Description: Set the Name of the selected Font
   //
   //  Inputs: String of the font name
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 22 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   void setFontName(String value)
   {
      mFontName = value;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: setFontSize
   //
   //  Description: Set the Size of the selected Font
   //
   //  Inputs: integer Value of the font size
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 22 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   void setFontSize(int value)
   {
      mFontSize = value;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: writePreferences
   //
   //  Description: Load the Prefercences Data from an xml file
   //
   //  Inputs: doc - Document node
   //
   //  Return: Constructed Node
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   Node writePreferences(Document doc)
   {
      Node  preferenceNode;                      //----- Preference Node
      Node  itemNode;                            //----- Value Node

      preferenceNode = doc.createElement(mPrefTag);

      if(mFontBold)
      {
         preferenceNode.appendChild(doc.createTextNode("\n\t\t"));
         itemNode = preferenceNode.appendChild(doc.createElement(mFontBoldTag));
         itemNode.appendChild(doc.createTextNode("true"));
	  }

      if(mFontItalic)
      {
         preferenceNode.appendChild(doc.createTextNode("\n\t\t"));
         itemNode = preferenceNode.appendChild(doc.createElement(mFontItalicTag));
         itemNode.appendChild(doc.createTextNode("true"));
	  }

      if(mFontName != mInitFontValue)
      {
         preferenceNode.appendChild(doc.createTextNode("\n\t\t"));
         itemNode = preferenceNode.appendChild(doc.createElement(mFontNameTag));
         itemNode.appendChild(doc.createTextNode(mFontName));
	  }

      if(mFontSize != mInitFontSize)
      {
         preferenceNode.appendChild(doc.createTextNode("\n\t\t"));
         itemNode = preferenceNode.appendChild(doc.createElement(mFontSizeTag));
         itemNode.appendChild(doc.createTextNode(String.valueOf(mFontSize)));
	  }

      if(mBackColor != Color.WHITE)
      {
         preferenceNode.appendChild(doc.createTextNode("\n\t\t"));
         itemNode = preferenceNode.appendChild(doc.createElement(mBackColorTag));
         itemNode.appendChild(doc.createTextNode(
            String.valueOf(mBackColor.getRGB())));
      }

      if(mTextColor != Color.BLACK)
      {
         preferenceNode.appendChild(doc.createTextNode("\n\t\t"));
         itemNode = preferenceNode.appendChild(doc.createElement(mTextColorTag));
         itemNode.appendChild(doc.createTextNode(
            String.valueOf(mTextColor.getRGB())));
      }

      preferenceNode.appendChild(doc.createTextNode("\n\t"));

      return preferenceNode;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: writeMenu
   //
   //  Description: write the Menu Data to an xml file
   //
   //  Inputs: rootNode - menu node
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 20 Feb 2007 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   Node writeMenu(Document doc)
   {
      Node  menuNode;                             //----- Menu Node
      Node  itemNode;                             //----- Value Node

      menuNode = doc.createElement(mMenuTag);

      return menuNode;
   }

   //////////////////////////////////////////////////////
   //
   //  Function: writeConfigFile
   //
   //  Description: write of the RSSData to specified xml file
   //
   //  Inputs: xmlString - name of the file to be written
   //          RSSList - Vector of RSSData values
   //
   //  Return: Nothing
   //
   //  Author: Robert Badger
   //
   //  Modification: 27 Aug 2006 (RTB) - Initial Version
   //
   ///////////////////////////////////////////////////////
   public void writeConfigFile(String xmlString)
   {
       DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
       Document doc;                                     //----- Document Node
       File file;                                        //----- output file class
       Result result;                                    //-----
       Source source;                                    //-----
       Transformer xformer;                              //-----
       Node  rootNode;                                   //----- Root node for xml tree
       int i;                                            //----- Loop Variable

       try {
          DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
          doc = docBuilder.newDocument();

          //----- Save Preferences
          rootNode = doc.appendChild(doc.createElement("VTSConfig"));

          rootNode.appendChild(doc.createTextNode("\n\t"));

          rootNode.appendChild(writePreferences(doc));

          //rootNode.appendChild(doc.createTextNode("\n\t"));

          //rootNode.appendChild(writeMenu(doc));

          rootNode.appendChild(doc.createTextNode("\n"));

          //----- Prepare the DOM document for writing
          source = new DOMSource(doc);

          //----- Prepare the output file
          file = new File(xmlString);
          result = new StreamResult(file);

          //----- Write the DOM document to the file
          xformer = TransformerFactory.newInstance().newTransformer();
          xformer.transform(source, result);
       } catch (TransformerConfigurationException e) {
       } catch (TransformerException e) {
       } catch (ParserConfigurationException pce) {
          //----- Parser with specified options can't be built
          pce.printStackTrace();
       }
   }
}