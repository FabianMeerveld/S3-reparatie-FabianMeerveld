#pragma once
#include <crt_CleanRTOS.h>



namespace crt
{
    class MelkenControl: public Task
    {
        enum State = {WachtenOpKoe,WachtenOpMelken,Melken};

        private:
        State state = WachtenOpKoe;
        Flag GestartFlag;
        Flag GestoptFlag;
        Flag RFIDFlag;
        Channel RFIDChannel;
        Channel LitersChannel;
        spelControl& SpelControl;
        DatabaseServer DB;

        MelkenControl(const char *taskName, unsigned int taskPriority, unsigned int taskSizeBytes, unsigned int taskCoreNumber, spelControl& SpelControl, DatabaseServer DB){
            GestartFlag(this);
            RFIDFlag(this);
            GestoptFlag(this);
            SpelControl(SpelControl);
            DB(DB);
        }
        public:
        void RFIDdetected(int ID){
            RFIDChannel.write(ID);
            RFIDflag.set()
        }
        void MelkenGestopt(float liters){
            LitersChannel.write(liters);
            gestoptFlag.set()
        }
        void MelkenGestart(){
            GestartFlag.set()
        }

        private:
        void main(){
            vTaskDelay(1000);
            while (true)
            {
                switch (state)
                {
                case WachtenOpKoe:
                    waitAny(RFIDFlag);
                    int KoeID = RFIDChannel.read();
                    RFIDFlag.clear();
                    state = WachtenOpMelken;
                    break;
                case WachtenOpMelken:
                    waitAny(GestartFlag);
                    GestartFlag.clear();
                    SpelControl.StartSpel();
                    state = Melken;
                    break;
                case Melken:
                    waitAny(GestoptFlag);
                    float Liters = LitersChannel.read();
                    GestoptFlag.Clear();
                    DatabaseServer.SendData(KoeID,Liters);
                    SpelControl.StopSpel();
                    state = WachtenOpKoe;
                    break;
                
                default:
                    break;
                }
            }
            
        }
    }



}