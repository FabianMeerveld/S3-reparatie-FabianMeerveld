#pragma once
#include <crt_CleanRTOS.h>
#include <crt_Button.h>



namespace crt
{
    enum State = {WachtenOpKoe,WachtenOpMelken,Melken};
    class MelkenControl: public Task, public IButtonListener
    {
        private:
        State state;
        Button buttonLinks;
		Button buttonRechts;
        Flag GestartFlagl;
        Channel RFIDChannel;
        Channel LitersChannel;
        spelControl& SpelControl;
        DatabaseServer DB;

    }

}