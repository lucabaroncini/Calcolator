#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Calcolatrice.h"

static int panelHandle;

int NUM_CTRL[16] = {PANEL_NUM_0,PANEL_NUM_1,PANEL_NUM_2,PANEL_NUM_3,PANEL_NUM_4,PANEL_NUM_5,PANEL_NUM_6,PANEL_NUM_7,PANEL_NUM_8,
				   PANEL_NUM_9,PANEL_NUM_10,PANEL_NUM_11,PANEL_NUM_12,PANEL_NUM_13,PANEL_NUM_14,PANEL_NUM_15},
	LED_CTRL[4] = {PANEL_LED_1,PANEL_LED_2,PANEL_LED_3,PANEL_LED_4},
	MODE_CTRL[4] = {PANEL_MODE_1,PANEL_MODE_2,PANEL_MODE_3,PANEL_MODE_4},
	VAL_CTRL[4] = {PANEL_HEX,PANEL_DEC,PANEL_OCT,PANEL_BIN},
	OPE_CTRL[6] = {PANEL_OPE_1,PANEL_OPE_2,PANEL_OPE_3,PANEL_OPE_4,PANEL_OPE_5,PANEL_OPE_6};

char valore[260],ris[4][260];
int mode = 2;
double val[2];
int ope = 0;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Calcolatrice.uir", PANEL)) < 0)
		return -1;
	SetCtrlVal (panelHandle, LED_CTRL[1], 1);
	SetCtrlVal (panelHandle, LED_CTRL[0], 0);
	SetCtrlVal (panelHandle, LED_CTRL[2], 0);
	SetCtrlVal (panelHandle, LED_CTRL[3], 0);
	DisplayPanel (panelHandle);
	int i;
	for(i=10;i<16;i++) SetCtrlAttribute (panelHandle, NUM_CTRL[i], ATTR_DIMMED, 1);
	
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK cbNum (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int i;
			for(i=0;i<16;i++)
			{
				if(control == NUM_CTRL[i])
				{
					if(i==10) sprintf(valore,"%sA",valore);
					else if(i==11) sprintf(valore,"%sB",valore);
					else if(i==12) sprintf(valore,"%sC",valore);
					else if(i==13) sprintf(valore,"%sD",valore);
					else if(i==14) sprintf(valore,"%sE",valore);
					else if(i==15) sprintf(valore,"%sF",valore);
					else sprintf(valore,"%s%d",valore,i);
				}
				SetCtrlVal (panel, PANEL_TEXT, valore);
			}

			break;
	}
	return 0;
}

int CVICALLBACK cbOpe (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
				char valore1[260];
				int i;
				int j;
				int oct[100];
				int bin[100];
				int temp;
				int vH;
				char vBin[100];
				
				if(control == OPE_CTRL[5])
				{
					GetCtrlVal (panel, PANEL_TEXT, valore); 
					sprintf(valore,"%s.",valore);
					SetCtrlVal (panel, PANEL_TEXT, valore); 
				}
				else
				{
					for(i=0;i<5;i++)
					{
						if(control == OPE_CTRL[i])
						{
							if(i<4)
							{
								GetCtrlVal (panel, PANEL_TEXT, valore);
								if(mode == 1) 
								{
									sscanf(valore,"%x",&vH);
									val[0] = (int)vH;
								}
								else if(mode == 2) sscanf(valore,"%lf",&val[0]);
								else if(mode == 3) 
								{
									sscanf(valore,"%o",&vH);
									val[0] = (int)vH;
								}
								else if(mode == 4) 
								{
									sscanf(valore,"%99[01]",vBin);
									val[0] = strtoul (vBin, NULL, 2); 
								}
								
								if(i == 0) 
								{
									sprintf(valore,"%s+",valore);
									ope = 1;
								}
								else if(i == 1) 
								{
									sprintf(valore,"%s-",valore);
									ope = 2;  
								}
								else if(i == 2) 
								{
									sprintf(valore,"%s*",valore);
									ope = 3;  
								}
								else if(i == 3) 
								{
									sprintf(valore,"%s/",valore);
									ope = 4;  
								}
								SetCtrlVal (panel, PANEL_TEXT_2, valore);
								memset (valore, 0, strlen(valore));
								SetCtrlVal (panel, PANEL_TEXT, valore);
								
							}
							else if(i == 4) 
							{
								if(ope>0)
								{
									if(mode == 1)
									{
										sscanf(valore,"%x",&vH);
										val[1] = (int)vH;
									}
									else if(mode == 2) sscanf(valore,"%lf",&val[1]);
									else if(mode == 3) 
									{
										sscanf(valore,"%o",&vH);
										val[1] = (int)vH;
									}
									else if(mode == 4) 
									{
										sscanf(valore,"%99[01]",vBin); 
										val[1] = strtoul (vBin, NULL, 2);
									}
  
									if (ope == 1) 
									{
										sprintf(ris[1],"%lf", val[0]+val[1]);
										if(val[0]+val[1] == (int)val[0]+(int)val[1])
										{
											sprintf(ris[0],"%X", (int)val[0]+(int)val[1]);
											//OCTAL
											i=0;
											temp = (int)val[0]+(int)val[1];
											while (temp!=0)
											{
												oct[i] = temp%8;
												temp/=8;
												i++;
											}
											for(j = i-1;j>=0;j--) sprintf(ris[2],"%s%d",ris[2], oct[j]);      
											//BINARIO
											i=0;
											temp = (int)val[0]+(int)val[1];
											while (temp!=0)
											{
												bin[i] = temp%2;
												temp/=2;
												i++;
											}
											for(j = i-1;j>=0;j--) sprintf(ris[3],"%s%d",ris[3], bin[j]);   
										}
										else
										{
											sprintf(ris[0],"ERR. decimal");
											sprintf(ris[2],"ERR. decimal");  
											sprintf(ris[3],"ERR. decimal");  
										}
									}
									else if (ope == 2) 
									{
										sprintf(ris[1],"%lf", val[0]-val[1]);
										if(val[0]-val[1] == (int)val[0]-(int)val[1])
										{
											sprintf(ris[0],"%X", (int)val[0]-(int)val[1]);
											//OCTAL
											i=0;
											temp = (int)val[0]-(int)val[1];
											while (temp!=0)
											{
												oct[i] = temp%8;
												temp/=8;
												i++;
											}
											for(j = i-1;j>=0;j--) sprintf(ris[2],"%s%d",ris[2], oct[j]);      
											//BINARIO
											i=0;
											temp = (int)val[0]-(int)val[1];
											while (temp!=0)
											{
												bin[i] = temp%2;
												temp/=2;
												i++;
											}
											for(j = i-1;j>=0;j--) sprintf(ris[3],"%s%d",ris[3], bin[j]);   
										
										}
										else
										{
											sprintf(ris[0],"ERR. decimal");
											sprintf(ris[2],"ERR. decimal");  
											sprintf(ris[3],"ERR. decimal");  
										}
									}
									else if (ope == 3) 
									{
										sprintf(ris[1],"%lf", val[0]*val[1]);
										if(val[0]*val[1] == (int)val[0]*(int)val[1])
										{
											sprintf(ris[0],"%X", (int)val[0]*(int)val[1]);
											//OCTAL
											i=0;
											temp = (int)val[0]*(int)val[1];
											while (temp!=0)
											{
												oct[i] = temp%8;
												temp/=8;
												i++;
											}
											for(j = i-1;j>=0;j--) sprintf(ris[2],"%s%d",ris[2], oct[j]);
											//BINARIO
											i=0;
											temp = (int)val[0]*(int)val[1];
											while (temp!=0)
											{
												bin[i] = temp%2;
												temp/=2;
												i++;
											}
											for(j = i-1;j>=0;j--) sprintf(ris[3],"%s%d",ris[3], bin[j]); 
										}
										else
										{
											sprintf(ris[0],"ERR. decimal");
											sprintf(ris[2],"ERR. decimal");  
											sprintf(ris[3],"ERR. decimal");  
										}
									}
									else if (ope == 4) 
									{
										sprintf(ris[1],"%lf", val[0]/val[1]);
										if(val[0]/val[1] == (int)val[0]/(int)val[1])
										{
											sprintf(ris[0],"%X", (int)val[0]/(int)val[1]);
											//OCTAL
											i=0;
											temp = (int)val[0]/(int)val[1];
											while (temp!=0)
											{
												oct[i] = temp%8;
												temp/=8;
												i++;
											}
											for(j = i-1;j>=0;j--) sprintf(ris[2],"%s%d",ris[2], oct[j]);   
											//BINARIO
											i=0;
											temp = (int)val[0]/(int)val[1];
											while (temp!=0)
											{
												bin[i] = temp%2;
												temp/=2;
												i++;
											}
											for(j = i-1;j>=0;j--) sprintf(ris[3],"%s%d",ris[3], bin[j]);   
										
										}
										else
										{
											sprintf(ris[0],"ERR. decimal");
											sprintf(ris[2],"ERR. decimal");  
											sprintf(ris[3],"ERR. decimal");  
										}
									}
									GetCtrlVal (panel, PANEL_TEXT_2, valore1);
									sprintf(valore1,"%s%s=",valore1,valore);
									SetCtrlVal (panel, PANEL_TEXT_2, valore1);
								}
								else
								{
									if(mode == 1) 
									{
										sscanf(valore,"%x",&vH);
										val[1] = (int)vH;
									}
									else if(mode == 2) sscanf(valore,"%lf",&val[1]);
									else if(mode == 3) 
									{
										sscanf(valore,"%o",&vH);
										val[1] = (int)vH;
									}

									sprintf(ris[1],"%lf", val[1]);
									if(val[1] == (int)val[1] && val[1]!=0)
									{
										sprintf(ris[0],"%X", (int)val[1]);
										//OCTAL
										i=0;
										temp = (int)val[1];
										while (temp!=0)
										{
											oct[i] = temp%8;
											temp/=8;
											i++;
										}
										for(j = i-1;j>=0;j--) sprintf(ris[2],"%s%d",ris[2], oct[j]);   
										//BINARIO
										i=0;
										temp = (int)val[1];
										while (temp!=0)
										{
											bin[i] = temp%2;
											temp/=2;
											i++;
										}
										for(j = i-1;j>=0;j--) sprintf(ris[3],"%s%d",ris[3], bin[j]);   
										
									}
									else
									{
										sprintf(ris[0],"ERR. decimal");
										sprintf(ris[2],"ERR. decimal");  
										sprintf(ris[3],"ERR. decimal");  
									}
									
								}
								sprintf(valore,"%s", ris[mode-1]); 
								SetCtrlVal (panel, PANEL_TEXT, ris[mode-1]);
								SetCtrlVal (panel, PANEL_HEX, ris[0]); 
								SetCtrlVal (panel, PANEL_DEC, ris[1]);
								SetCtrlVal (panel, PANEL_OCT, ris[2]);
								SetCtrlVal (panel, PANEL_BIN, ris[3]);
								memset (ris[2], 0, strlen(ris[2]));
								memset (ris[3], 0, strlen(ris[3]));
								ope = 0;
								break;
							}
						}
					}
				}
			break;
	}
	return 0;
}

int CVICALLBACK cbCanc (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				 if(control == PANEL_CANC)
				 {
					 memset (valore, 0, strlen(valore));
					 val[0]=val[1]=0;
					 SetCtrlVal (panel, PANEL_TEXT, "0");
					 SetCtrlVal (panel, PANEL_TEXT_2, "0");
					 SetCtrlVal (panel, PANEL_HEX, "0");
					 SetCtrlVal (panel, PANEL_DEC, "0");
					 SetCtrlVal (panel, PANEL_OCT, "0");
					 SetCtrlVal (panel, PANEL_BIN, "0");
					 
				 }
				 else
				 {
					 memset (valore, 0, strlen(valore)); 
					 val[1] = 0;
					 SetCtrlVal (panel, PANEL_TEXT, "0");
				 }
			break;
	}
	return 0;
}

int CVICALLBACK cbQuit (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK cbMode (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				int i;
				for(i=0;i<4;i++)
				{
					if(control == MODE_CTRL[i])
					{
						SetCtrlVal (panelHandle, LED_CTRL[mode-1], 0);
						SetCtrlVal (panelHandle, LED_CTRL[i], 1);
						mode = i+1; 
						GetCtrlVal (panel, VAL_CTRL[i], valore);
						SetCtrlVal (panel, PANEL_TEXT, valore); 
					}
				}
				if(mode == 1)
				{
					for(i=10;i<16;i++) SetCtrlAttribute (panel, NUM_CTRL[i], ATTR_DIMMED, 0);
					SetCtrlAttribute (panel, OPE_CTRL[5], ATTR_DIMMED, 1);
					for(i=2;i<10;i++) SetCtrlAttribute (panel, NUM_CTRL[i], ATTR_DIMMED, 0); 
				}
				else 
				{
					if(mode == 3)
					{
						for(i=8;i<10;i++) SetCtrlAttribute (panel, NUM_CTRL[i], ATTR_DIMMED, 1);
						for(i=2;i<8;i++) SetCtrlAttribute (panel, NUM_CTRL[i], ATTR_DIMMED, 0); 
						SetCtrlAttribute (panel, OPE_CTRL[5], ATTR_DIMMED, 1);   
					}
					else if(mode == 4)
					{
						for(i=2;i<10;i++) SetCtrlAttribute (panel, NUM_CTRL[i], ATTR_DIMMED, 1);
						SetCtrlAttribute (panel, OPE_CTRL[5], ATTR_DIMMED, 1);   
					}
					else 
					{
						for(i=2;i<10;i++) SetCtrlAttribute (panel, NUM_CTRL[i], ATTR_DIMMED, 0);
						SetCtrlAttribute (panel, OPE_CTRL[5], ATTR_DIMMED, 0);   
					}
					for(i=10;i<16;i++) SetCtrlAttribute (panel, NUM_CTRL[i], ATTR_DIMMED, 1);
				}
				memset (valore, 0, strlen(valore));  
			break;
	}
	return 0;
}
