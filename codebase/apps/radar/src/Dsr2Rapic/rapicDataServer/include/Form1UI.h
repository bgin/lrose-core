
//////////////////////////////////////////////////////////////
//
// Header file for Form1UI
//
//    This file is generated by RapidApp 1.2
//
//    This class implements the user interface portion of a class
//    Normally it is not used directly.
//    Instead the subclass, Form1 is instantiated
//
//    To extend or alter the behavior of this class, you should
//    modify the Form1 files
//
//    Restrict changes to those sections between
//    the "//--- Start/End editable code block" markers
//
//    This will allow RapidApp to integrate changes more easily
//
//    This class is a ViewKit user interface "component".
//    For more information on how components are used, see the
//    "ViewKit Programmers' Manual", and the RapidApp
//    User's Guide.
//
//////////////////////////////////////////////////////////////
#ifndef FORM1UI_H
#define FORM1UI_H
#include <Vk/VkComponent.h>


//---- Start editable code block: headers and declarations


//---- End editable code block: headers and declarations


class Form1UI : public VkComponent
{ 

  public:

    Form1UI ( const char *, Widget );
    Form1UI ( const char * );
    ~Form1UI();
    void create ( Widget );
    const char *  className();

    //---- Start editable code block: Form1 public


    //---- End editable code block: Form1 public


  protected:


    // Widgets created by this class

    Widget  _form1;
    Widget  _scale;
    Widget  _scale1;
    Widget  _textfield;
    Widget  _textfield1;


    //---- Start editable code block: Form1 protected


    //---- End editable code block: Form1 protected


  private: 

    // Array of default resources

    static String      _defaultForm1UIResources[];

    //---- Start editable code block: Form1 private


    //---- End editable code block: Form1 private
};
//---- Start editable code block: End of generated code


//---- End editable code block: End of generated code

#endif

