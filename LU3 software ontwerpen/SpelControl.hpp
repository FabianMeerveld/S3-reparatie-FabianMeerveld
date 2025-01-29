#pragma once
#include <crt_CleanRTOS.h>
#include <crt_Button.h>



namespace crt
{
    class SpelControl: public Task, public ButtonListener
    {
        enum State = {Actief, Idle};
        enum SubState = {WachtenOpKnik,Geluid,WachtOpStap,LinksOpgetild,RechtsOpgetild};

        private:
        State state = Idle;
        SubState subState = WachtenOpKnik;
        Channel KnopLosgelatenChannel;
        Channel KnopIngedruktChannel;
        Flag KnikFlag;
        Flag SoundKlaarFlag;
        Flag IngedruktFlag;
        Flag LosgelatenFlag;
        Flag StartFlag;
        Flag StopFlag;
        Timer StapTimer;
        BuzzerControl Buzzer;
        MotorControl Motor;
        SolonoidControl Solonoid;

        MelkenControl(const char *taskName, unsigned int taskPriority, unsigned int taskSizeBytes, unsigned int taskCoreNumber,ButtonHandler& buttonHandler, BuzzerControl Buzzer, MotorControl Motor, SolonoidControl Solonoid){
            KnikFlag(this);
            SoundKlaarFlag(this);
            IngedruktFlag(this);
            LosgelatenFlag(this);
            Buzzer(BuzzerControl);
            Motor(MotorControl);
            Solonoid(SolonoidControl);
        }
        public:
        void KnopIngedrukt(eButtonID ButtonID){
            KnopIngedruktChannel.write(ID);
            IngedruktFlag.set()
        }
        void KnopLosgelaten(eButtonID ButtonID){
            KnopLosgelatenChannel.write(ID);
            LosgelatenFlag.set()
        }
        void StartSpel(){
            StartFlag.set()
        }
        void StopSpel(){
            StopFlag.set()
        }
        void SoundKlaar(){
            SoundKlaarFlag.set()
        }
        void KnikGedetecteerd(){
            KnikFlag.set()
        }

        private:
        void main(){
            vTaskDelay(1000);
            while (true)
            {
                switch (state)
                {
                case Idle:
                    waitAny(StartFlag);
                    StartFlag.clear();
                    state = Actief;
                    subState = Wachten;
                    break;
                case Actief:
                    switch (subState)
                    {
                        case WachtenOpKnik:
                            waitAny(StopFlag, KnikFlag);
                            if hasFired(StopFlag){
                                state = Idle;
                                StopFlag.clear();
                            } else if hasFired(KnikFlag){
                                subState = Geluid;
                                KnikFlag.clear();
                                Buzzer.MakeSound();
                            }

                        case Geluid:
                            waitAny(StopFlag, SoundKlaarFlag);
                            if hasFired(StopFlag){
                                state = Idle;
                                StopFlag.clear();
                            } else if hasFired(SoundKlaarFlag){
                                subState = WachtOpStap;
                                StapTimer.start(1000000);
                            }

                        case WachtOpStap:
                            waitAny(StopFlag, StapTimer, IngedruktFlag);
                            if hasFired(StopFlag){
                                state = Idle;
                                StopFlag.clear();
                            } else if hasFired(StapTimer){
                                subState = Wachten;
                                StapTimer.clear();
                            } else if hasFired(IngedruktFlag){
                                KnopID = KnopIngedruktChannel.read();
                                IngedruktFlag.clear();
                                if (KnopID == KnopLinksID){
                                    subState = LinksOpgetild;
                                } else if (KnopID == KnopRechtsID){
                                    subState = RechtsOpgetild;
                                }
                            }

                        case LinksOpgetild:
                            waitAny(StopFlag, StapTimer,LosgelatenFlag);
                            if hasFired(StopFlag){
                                state = Idle;
                                StopFlag.clear();
                            } else if hasFired(StapTimer){
                                subState = Wachten;
                                StapTimer.clear();
                            } else if hasFired(LosgelatenFlag){
                                KnopID = KnopLosgelatenChannel.read();
                                LosgelatenFlag.clear();
                                if (KnopID == KnopLinksID){
                                    subState = wachten;
                                    Motor.GeefVoer();
                                } else if (KnopID == KnopRechtsID){
                                    subState = wachten;
                                }
                            }

                        case RechtsOpgetild:
                            waitAny(StopFlag, StapTimer,LosgelatenFlag);
                            if hasFired(StopFlag){
                                state = Idle;
                                StopFlag.clear();
                            } else if hasFired(StapTimer){
                                subState = Wachten;
                                StapTimer.clear();
                            } else if hasFired(LosgelatenFlag){
                                KnopID = KnopLosgelatenChannel.read();
                                LosgelatenFlag.clear();
                                if (KnopID == KnopLinksID){
                                    subState = wachten;
                                } else if (KnopID == KnopRechtsID){
                                    subState = wachten;
                                    Solenoid.GeefWater();
                                }
                            }

                        default:
                            break;
                    }
                
                default:
                    break;
                }
            }
            
        }
    }



}