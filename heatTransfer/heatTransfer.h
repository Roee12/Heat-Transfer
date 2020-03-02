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

#define  PANEL                            1       /* callback function: panelFunc */
#define  PANEL_TEMP_BODY_2                2       /* control type: scale, callback function: changeBody2 */
#define  PANEL_TEMP_BODY_1                3       /* control type: scale, callback function: changeBody1 */
#define  PANEL_CONDUCTOR                  4       /* control type: deco, callback function: (none) */
#define  PANEL_CONTROL_BUTTON             5       /* control type: textButton, callback function: controlFunc */
#define  PANEL_MASS_BODY_2                6       /* control type: numeric, callback function: (none) */
#define  PANEL_C_BODY_2                   7       /* control type: numeric, callback function: (none) */
#define  PANEL_MASS_BODY_1                8       /* control type: numeric, callback function: (none) */
#define  PANEL_BODY_1                     9       /* control type: deco, callback function: (none) */
#define  PANEL_C_BODY_1                   10      /* control type: numeric, callback function: (none) */
#define  PANEL_S_CONDUCTOR                11      /* control type: numeric, callback function: (none) */
#define  PANEL_TIMER_INTERVAL             12      /* control type: numeric, callback function: (none) */
#define  PANEL_BODY_2                     13      /* control type: deco, callback function: (none) */
#define  PANEL_TIMER                      14      /* control type: timer, callback function: timerFunc */
#define  PANEL_ADD_THERMAL_ENERGY_1       15      /* control type: numeric, callback function: addEnergyFunc */
#define  PANEL_ADD_THERMAL_ENERGY_2       16      /* control type: numeric, callback function: addEnergyFunc */
#define  PANEL_LINK_BUTTON                17      /* control type: command, callback function: linkFunc */
#define  PANEL_RESET_BUTTON               18      /* control type: command, callback function: resetFunc */
#define  PANEL_GRAPHS_PANEL               19      /* control type: command, callback function: showSecondPanel */
#define  PANEL_ABOUT                      20      /* control type: command, callback function: showInfoFunc */
#define  PANEL_MATERIAL_OPTIONS_2         21      /* control type: ring, callback function: changeData2 */
#define  PANEL_MATERIAL_OPTIONS_1         22      /* control type: ring, callback function: changeData1 */
#define  PANEL_SHOW_TIME                  23      /* control type: numeric, callback function: (none) */
#define  PANEL_DECORATION                 24      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_2               25      /* control type: deco, callback function: (none) */
#define  PANEL_SPLITTER                   26      /* control type: splitter, callback function: (none) */
#define  PANEL_SPLITTER_2                 27      /* control type: splitter, callback function: (none) */
#define  PANEL_DECORATION_3               28      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_4               29      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_5               30      /* control type: deco, callback function: (none) */
#define  PANEL_CONTROL_TITLE              31      /* control type: textMsg, callback function: (none) */
#define  PANEL_DATA_TITLE                 32      /* control type: textMsg, callback function: (none) */
#define  PANEL_SYSTEM_TITLE               33      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEMP_TITLE                 34      /* control type: textMsg, callback function: (none) */
#define  PANEL_BODY1_TITLE_1              35      /* control type: textMsg, callback function: (none) */
#define  PANEL_BODY1_TITLE_2              36      /* control type: textMsg, callback function: (none) */
#define  PANEL_BODY2_TITLE_1              37      /* control type: textMsg, callback function: (none) */
#define  PANEL_BODY2_TITLE_2              38      /* control type: textMsg, callback function: (none) */
#define  PANEL_COND_TITLE_1               39      /* control type: textMsg, callback function: (none) */
#define  PANEL_BODY1_TITLE_3              40      /* control type: textMsg, callback function: (none) */
#define  PANEL_BODY2_TITLE_3              41      /* control type: textMsg, callback function: (none) */
#define  PANEL_UNITS_ADD_ENERGY_1         42      /* control type: textMsg, callback function: (none) */
#define  PANEL_COND_TITLE_2               43      /* control type: textMsg, callback function: (none) */
#define  PANEL_UNITS_ADD_ENERGY_2         44      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEMP_SELECT_TITLE          45      /* control type: textMsg, callback function: (none) */
#define  PANEL_VIDEO_TITLE                46      /* control type: textMsg, callback function: (none) */

#define  PANEL_2                          2       /* callback function: panelFunc2 */
#define  PANEL_2_RING                     2       /* control type: ring, callback function: (none) */
#define  PANEL_2_PLOT_GRAPH               3       /* control type: command, callback function: plotGraphsFunc */
#define  PANEL_2_CLS                      4       /* control type: command, callback function: clearFunc */
#define  PANEL_2_VALUE_CURSOR             5       /* control type: numeric, callback function: (none) */
#define  PANEL_2_TIME_CURSOR              6       /* control type: numeric, callback function: (none) */
#define  PANEL_2_GRAPH                    7       /* control type: graph, callback function: graphFunc */
#define  PANEL_2_LINEAR_FIT               8       /* control type: command, callback function: fitLineFunc */
#define  PANEL_2_LINEAR_ERROR             9       /* control type: numeric, callback function: (none) */
#define  PANEL_2_INTERCEPT                10      /* control type: numeric, callback function: (none) */
#define  PANEL_2_SLOPE                    11      /* control type: numeric, callback function: (none) */
#define  PANEL_2_TRUE_SLOPE               12      /* control type: numeric, callback function: (none) */
#define  PANEL_2_COLOR                    13      /* control type: color, callback function: plotGraphsFunc */
#define  PANEL_2_DECORATION               14      /* control type: deco, callback function: (none) */
#define  PANEL_2_DECORATION_2             15      /* control type: deco, callback function: (none) */
#define  PANEL_2_CURSOR_TITLE             16      /* control type: textMsg, callback function: (none) */
#define  PANEL_2_LINEAR_TITLE             17      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK addEnergyFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK changeBody1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK changeBody2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK changeData1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK changeData2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clearFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK controlFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fitLineFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK graphFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK linkFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelFunc(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelFunc2(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK plotGraphsFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK resetFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK showInfoFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK showSecondPanel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timerFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
