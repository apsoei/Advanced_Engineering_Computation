#ifndef GUI_IS_INCLUDED
#define GUI_IS_INCLUDED
/* { */

#include <vector>
#include <memory>
#include <string>

class CheapGUI
{
public:
	class Widget
	{
	public:
		int x0,y0,wid,hei;
		unsigned int r,g,b,a;
		std::string label;
		const CheapGUI *guiPtr;
		bool hide;
		bool active;

		Widget();
		void Show(void);
		void Hide(void);
		void SetColor(int r,int g,int b,int a);
		virtual ~Widget(){}
		virtual void Draw(void){}
		virtual void DrawInactive(void){}
		virtual void Clicked(void){};
	};
	class Text : public Widget
	{
	public:
		void SetText(const char str[]);
		virtual void Draw(void);
		virtual void DrawInactive(void)
		{
			Draw();
		}
	};
	class TextInput : public Widget
	{
	private:
		mutable bool edited;

	public:
		TextInput();
		void SetText(const char str[]);
		std::string GetText(void) const;
		void NotifyChar(char c);
		virtual void Draw(void);
		virtual void DrawInactive(void){}
		bool Edited(void);
	};
	class Button : public Widget
	{
	public:
		bool mouseOn;
		bool heldDown;
		virtual void DrawInactive(void){}
		Button();
	};
	class PushButton : public Button
	{
		virtual void Draw(void);
	};
	class CheckBox : public Button
	{
	private:
		bool checked;
		std::vector <CheckBox *> radioBtnGrp;
	public:
		CheckBox();
		void SetCheck(bool c);
		bool GetCheck(void) const;
		void SetRadioButtonGroup(const std::vector <CheckBox *> &grp);
		virtual void Draw(void);
		virtual void Clicked(void);
	};

	mutable bool needRedraw;
	Widget *lastClick;
	std::vector <std::shared_ptr <Widget> > widgetList;

	CheapGUI();
	Text *AddText(int x0,int y0,int wid,int hei,const char label[]);
	TextInput *AddTextInput(int x0,int y0,int wid,int hei,const char label[]);
	PushButton *AddPushButton(int x0,int y0,int wid,int hei,const char label[]);
	CheckBox *AddCheckBox(int x0,int y0,int wid,int hei,const char label[]);
	void SetRadioButtonGroup(const std::vector <CheckBox *> &grp);

	void Draw(void) const;

	Widget *GetActive(void);
	const Widget *GetActive(void) const;
	void MakeAllInactive(void);

	void NotifyMousePosition(int mx,int my);
	void NotifyChar(char c);
	void NotifyLButtonUp(int mx,int my);
	const Widget *PeekLastClicked(void) const;
	Widget *PeekLastClicked(void);
	Widget *GetLastClicked(void);

	static void CreateBitmapFontRenderer(void);
	static void SetBitmapFontRendererViewportSize(int wid,int hei);
	static void DeleteBitmapFontRenderer(void);
};


/* } */
#endif
