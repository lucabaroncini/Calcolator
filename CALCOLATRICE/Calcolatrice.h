/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_NUM_0                      2       /* control type: command, callback function: cbNum */
#define  PANEL_NUM_9                      3       /* control type: command, callback function: cbNum */
#define  PANEL_NUM_8                      4       /* control type: command, callback function: cbNum */
#define  PANEL_NUM_7                      5       /* control type: command, callback function: cbNum */
#define  PANEL_NUM_6                      6       /* control type: command, callback function: cbNum */
#define  PANEL_NUM_5                      7       /* control type: command, callback function: cbNum */
#define  PANEL_NUM_4                      8       /* control type: command, callback function: cbNum */
#define  PANEL_NUM_3                      9       /* control type: command, callback function: cbNum */
#define  PANEL_NUM_2                      10      /* control type: command, callback function: cbNum */
#define  PANEL_NUM_15                     11      /* control type: command, callback function: cbNum */
#define  PANEL_NUM_14                     12      /* control type: command, callback function: cbNum */
#define  PANEL_NUM_13                     13      /* control type: command, callback function: cbNum */
#define  PANEL_NUM_12                     14      /* control type: command, callback function: cbNum */
#define  PANEL_NUM_11                     15      /* control type: command, callback function: cbNum */
#define  PANEL_NUM_10                     16      /* control type: command, callback function: cbNum */
#define  PANEL_OPE_6                      17      /* control type: command, callback function: cbOpe */
#define  PANEL_OPE_3                      18      /* control type: command, callback function: cbOpe */
#define  PANEL_CANC_2                     19      /* control type: command, callback function: cbCanc */
#define  PANEL_CANC                       20      /* control type: command, callback function: cbCanc */
#define  PANEL_OPE_5                      21      /* control type: command, callback function: cbOpe */
#define  PANEL_OPE_4                      22      /* control type: command, callback function: cbOpe */
#define  PANEL_OPE_2                      23      /* control type: command, callback function: cbOpe */
#define  PANEL_OPE_1                      24      /* control type: command, callback function: cbOpe */
#define  PANEL_NUM_1                      25      /* control type: command, callback function: cbNum */
#define  PANEL_COMMANDBUTTON              26      /* control type: command, callback function: cbQuit */
#define  PANEL_MODE_4                     27      /* control type: command, callback function: cbMode */
#define  PANEL_MODE_3                     28      /* control type: command, callback function: cbMode */
#define  PANEL_MODE_2                     29      /* control type: command, callback function: cbMode */
#define  PANEL_MODE_1                     30      /* control type: command, callback function: cbMode */
#define  PANEL_LED_4                      31      /* control type: LED, callback function: (none) */
#define  PANEL_LED_3                      32      /* control type: LED, callback function: (none) */
#define  PANEL_LED_2                      33      /* control type: LED, callback function: (none) */
#define  PANEL_LED_1                      34      /* control type: LED, callback function: (none) */
#define  PANEL_HEX                        35      /* control type: textMsg, callback function: (none) */
#define  PANEL_OCT                        36      /* control type: textMsg, callback function: (none) */
#define  PANEL_BIN                        37      /* control type: textMsg, callback function: (none) */
#define  PANEL_DEC                        38      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXT                       39      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXT_2                     40      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK cbCanc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK cbMode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK cbNum(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK cbOpe(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK cbQuit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
