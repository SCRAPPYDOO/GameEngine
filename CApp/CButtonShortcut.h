#ifndef _CBUTTONSHORTCUT_H_
    #define _CBUTTONSHORTCUT_H_

#include "CButton.h"

class CButtonShortcut : public CButton
{
	private:
		CButton* pOriginalButton;

	public:
        CButtonShortcut(CButton* OriginalButton) 
		{
			w = 30;
			h = 30;
			nButtonFlag = 0;
			nPreviousX = x;
			nPreviousY = y;

			pButtonSurface = NULL;
			eButtonState = BUTTONSTATE_UNSELECTED;
			eAnimationState = BUTTON_ANIME_NORMAL;
			eButtonClass = BUTTONCLASS_SHORTCUT;
			pOriginalButton = OriginalButton;
		}
		~CButtonShortcut() {}

    public:
		bool OnLoad()
		{
			if(CButton::OnLoad(pOriginalButton->GetButtonType()))
				return true;

			return false;
		}

		void Activate()
		{
			if(pOriginalButton)
				pOriginalButton->Activate();

		}
};

#endif