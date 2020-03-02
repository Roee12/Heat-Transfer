#include <cvintwrk.h>
#include <analysis.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "heatTransfer.h"

static int panelHandle,panelHandle2;

double s,dt,t;
double addq1,addq2;
double *time_arr,*t1_arr,*t2_arr,*delta_arr,*log_delta_arr;
int counter = 0;
int color;

typedef struct
{
	double mass;
	double capacity;
	double temperature;
} body;

body body1,body2;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "heatTransfer.uir", PANEL)) < 0)
		return -1;
	if ((panelHandle2 = LoadPanel (0, "heatTransfer.uir", PANEL_2)) < 0)
		return -1;
	time_arr=(double*)calloc(1,sizeof(double));
	t1_arr=(double*)calloc(1,sizeof(double));
	t2_arr=(double*)calloc(1,sizeof(double));
	delta_arr=(double*)calloc(1,sizeof(double));
	log_delta_arr=(double*)calloc(1,sizeof(double));
	DisplayPanel (panelHandle);
	RunUserInterface ();
	free(time_arr);
	free(t1_arr);
	free(t2_arr);
	free(delta_arr);
	free(log_delta_arr);
	DiscardPanel (panelHandle);
	DiscardPanel (panelHandle2);
	return 0;
}

int CVICALLBACK panelFunc (int panel, int event, void *callbackData,
						   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}



int CVICALLBACK controlFunc (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int state;
	switch (event)
	{
		case EVENT_COMMIT:
			
		
			
			GetCtrlVal(panelHandle,PANEL_MASS_BODY_1,&body1.mass);
			GetCtrlVal(panelHandle,PANEL_MASS_BODY_2,&body2.mass);
			GetCtrlVal(panelHandle,PANEL_TEMP_BODY_1,&body1.temperature);
			GetCtrlVal(panelHandle,PANEL_TEMP_BODY_2,&body2.temperature);
			GetCtrlVal(panelHandle,PANEL_C_BODY_1,&body1.capacity);
			GetCtrlVal(panelHandle,PANEL_C_BODY_2,&body2.capacity);
			GetCtrlVal(panelHandle,PANEL_S_CONDUCTOR,&s);
			
			SetCtrlAttribute (panelHandle, PANEL_TIMER_INTERVAL, ATTR_CTRL_MODE, VAL_HOT);
			
			GetCtrlVal(panelHandle,PANEL_TIMER_INTERVAL,&dt);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_INTERVAL, dt);
			
			GetCtrlVal(panelHandle,PANEL_CONTROL_BUTTON,&state);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED,state);
			SetCtrlAttribute (panelHandle, PANEL_TEMP_SELECT_TITLE, ATTR_VISIBLE, 0);

		

			break;
	}
	return 0;
}

int CVICALLBACK timerFunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	double i1,i2;
	double dt1,dt2;
	double q1,q2;
	double redVal1,redVal2;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			
			SetCtrlAttribute (panelHandle, PANEL_TIMER_INTERVAL, ATTR_CTRL_MODE, VAL_INDICATOR);
			if (t<120)
			{
			    if ((fabs(body1.temperature - body2.temperature) > 0.001))
			      {
			          time_arr=(double*)realloc(time_arr,(counter+1)*sizeof(double));
			          t1_arr=(double*)realloc(t1_arr,(counter+1)*sizeof(double));
			          t2_arr=(double*)realloc(t2_arr,(counter+1)*sizeof(double));
			          delta_arr=(double*)realloc(delta_arr,(counter+1)*sizeof(double));
			          log_delta_arr=(double*)realloc(log_delta_arr,(counter+1)*sizeof(double));
			          time_arr[counter]=dt*counter;	
			          t1_arr[counter]= body1.temperature;
			          t2_arr[counter]= body2.temperature;
			          delta_arr[counter]=(body2.temperature - body1.temperature);
			          log_delta_arr[counter]=log (fabs(body2.temperature -body1.temperature));
			          counter++;
			          i1=(body2.temperature-body1.temperature)*(s*1000);
		              i2=(body1.temperature-body2.temperature)*(s*1000);
			          q1=i1*dt;
			          q2=i2*dt;
			          q1+=(addq1*1000);
			          q2+=(addq2*1000);
			          dt1=q1/(body1.mass * (body1.capacity*1000));
			          dt2=q2/(body2.mass * (body2.capacity*1000));
			          body1.temperature +=dt1;
			          body2.temperature +=dt2;
			          redVal1 = (body1.temperature/200) * 255;
			          redVal2 = (body2.temperature/200) * 255;
			          SetCtrlVal(panelHandle,PANEL_TEMP_BODY_1,body1.temperature);
		              SetCtrlVal(panelHandle,PANEL_TEMP_BODY_2,body2.temperature);
			          SetCtrlAttribute (panelHandle, PANEL_BODY_1, ATTR_FRAME_COLOR, MakeColor(redVal1,0,0));
			          SetCtrlAttribute (panelHandle, PANEL_BODY_2, ATTR_FRAME_COLOR, MakeColor(redVal2,0,0));
			          SetCtrlAttribute (panelHandle, PANEL_TEMP_BODY_1, ATTR_FILL_COLOR, MakeColor(redVal1,0,0));
			          SetCtrlAttribute (panelHandle, PANEL_TEMP_BODY_2, ATTR_FILL_COLOR, MakeColor(redVal2,0,0));
			          t+=dt;
			          SetCtrlVal(panelHandle,PANEL_SHOW_TIME,t);
			      }
			      else
			        {
				        SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED,0);
				        SetCtrlVal(panelHandle,PANEL_CONTROL_BUTTON,0);
				        MessagePopup("Message","The bodies are in thermal equilibrium!");
		         	}
			}
			else
			{
				
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED,0);
				SetCtrlVal(panelHandle,PANEL_CONTROL_BUTTON,0);
				MessagePopup("Error","The experiment takes too long!\nReset the system and select new values!");
			}
			break;
															 
	}
	return 0;
}

int CVICALLBACK changeBody1 (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	double val,setVal;
	switch (event)
	{
		case EVENT_VAL_CHANGED:

			 GetCtrlVal(panelHandle,PANEL_TEMP_BODY_1,&val);
			 setVal= (val/200) *255;
			 SetCtrlAttribute (panelHandle, PANEL_BODY_1, ATTR_FRAME_COLOR, MakeColor(setVal,0,0));
			 SetCtrlAttribute (panelHandle, PANEL_TEMP_BODY_1, ATTR_FILL_COLOR, MakeColor(setVal,0,0));

			
			break;
	}
	return 0;
}

int CVICALLBACK changeBody2 (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	double val,setVal;
	switch (event)
	{
		case EVENT_VAL_CHANGED:

			 GetCtrlVal(panelHandle,PANEL_TEMP_BODY_2,&val);
			 setVal= (val/200) *255;
			 SetCtrlAttribute (panelHandle, PANEL_BODY_2, ATTR_FRAME_COLOR, MakeColor(setVal,0,0));
			 SetCtrlAttribute (panelHandle, PANEL_TEMP_BODY_2, ATTR_FILL_COLOR, MakeColor(setVal,0,0));
	}
	return 0;
}


int CVICALLBACK addEnergyFunc (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED,0);
			GetCtrlVal(panelHandle,PANEL_ADD_THERMAL_ENERGY_1,&addq1);
			GetCtrlVal(panelHandle,PANEL_ADD_THERMAL_ENERGY_2,&addq2);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED,1);

			break;
	}
	return 0;
}

int CVICALLBACK resetFunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			if (ConfirmPopup ("Message", "Are you sure you want to reset the system?"))
			{
			t=0;
			counter=0;
			SetCtrlVal(panelHandle,PANEL_SHOW_TIME,0.00);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED,0);
			SetCtrlVal(panelHandle,PANEL_TEMP_BODY_1,0.00);
		    SetCtrlVal(panelHandle,PANEL_TEMP_BODY_2,0.00);
			SetCtrlAttribute (panelHandle, PANEL_BODY_1, ATTR_FRAME_COLOR, MakeColor(0,0,0));
			SetCtrlAttribute (panelHandle, PANEL_BODY_2, ATTR_FRAME_COLOR, MakeColor(0,0,0));
			SetCtrlAttribute (panelHandle, PANEL_TEMP_BODY_1, ATTR_FILL_COLOR, MakeColor(0,0,0));
			SetCtrlAttribute (panelHandle, PANEL_TEMP_BODY_2, ATTR_FILL_COLOR, MakeColor(0,0,0));
			SetCtrlVal(panelHandle,PANEL_CONTROL_BUTTON,0);
			SetCtrlVal(panelHandle,PANEL_ADD_THERMAL_ENERGY_1,0.00);
			SetCtrlVal(panelHandle,PANEL_ADD_THERMAL_ENERGY_2,0.00); 
			SetCtrlAttribute (panelHandle, PANEL_TIMER_INTERVAL, ATTR_CTRL_MODE, VAL_HOT);
			DeleteGraphPlot (panelHandle2, PANEL_2_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			SetCtrlAttribute (panelHandle, PANEL_TEMP_SELECT_TITLE, ATTR_VISIBLE, 1);
			HidePanel (panelHandle2);

			}
			else
			{
				break;
			}
			break;
	}
	return 0;
}

int CVICALLBACK panelFunc2 (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel (panelHandle2);
			break;
	}
	return 0;
}

int CVICALLBACK showSecondPanel (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if (counter !=0)
			{
				DisplayPanel(panelHandle2);
			}
			else
			{
				MessagePopup ("Error", "Run the system!");
			}
			break;
	}
	return 0;
}

int CVICALLBACK clearFunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DeleteGraphPlot (panelHandle2, PANEL_2_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			SetCtrlAttribute (panelHandle2, PANEL_2_COLOR, ATTR_VISIBLE, 1);
			break;
	}
	return 0;
}

int CVICALLBACK plotGraphsFunc (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	int selection;

	switch (event)
	{
		case EVENT_COMMIT:
			
			SetCtrlAttribute (panelHandle2, PANEL_2_COLOR, ATTR_VISIBLE, 1);
			GetCtrlVal(panelHandle2,PANEL_2_COLOR,&color);
			GetCtrlVal(panelHandle2,PANEL_2_RING,&selection);
			
			switch (selection)
			{
				case 1:
					   PlotXY (panelHandle2, PANEL_2_GRAPH, time_arr, t1_arr, counter, VAL_DOUBLE, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, color);
					break;
				case 2:
					   PlotXY (panelHandle2, PANEL_2_GRAPH, time_arr, t2_arr, counter, VAL_DOUBLE, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, color);
					break;
				case 3:
					   PlotXY (panelHandle2, PANEL_2_GRAPH, time_arr, delta_arr, counter, VAL_DOUBLE, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, color);
					break;
				case 4:
					   PlotXY (panelHandle2, PANEL_2_GRAPH, time_arr,log_delta_arr, counter, VAL_DOUBLE, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, color);
					break;
			}
				
			break;
	}				   
	return 0;
}

int CVICALLBACK graphFunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	double time,value;
	switch (event)
	{
		case EVENT_COMMIT:
			GetGraphCursor (panelHandle2, PANEL_2_GRAPH, 1, &time, &value);
			SetCtrlVal(panelHandle2,PANEL_2_TIME_CURSOR,time);
			SetCtrlVal(panelHandle2,PANEL_2_VALUE_CURSOR,value);
			break;
	}
	return 0;
}

int CVICALLBACK fitLineFunc (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{

	double slope,intercept,error,trueslope;
	switch (event)
	{
		case EVENT_COMMIT:
			if (counter != 0)
			{
			double linear_arr[counter];
			SetCtrlAttribute (panelHandle2, PANEL_2_COLOR, ATTR_VISIBLE, 0);
			LinFit (time_arr, log_delta_arr, counter, linear_arr, &slope, &intercept, &error);
			PlotXY (panelHandle2, PANEL_2_GRAPH, time_arr, linear_arr, counter, VAL_DOUBLE, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_GREEN);
			SetCtrlVal(panelHandle2,PANEL_2_SLOPE,slope);
			SetCtrlVal(panelHandle2,PANEL_2_INTERCEPT,intercept);
			SetCtrlVal(panelHandle2,PANEL_2_LINEAR_ERROR,error);
			trueslope=-s*((body1.mass*body1.capacity)+(body2.mass*body2.capacity))/(body1.mass*body1.capacity*body2.mass*body2.capacity);
			SetCtrlVal(panelHandle2,PANEL_2_TRUE_SLOPE,trueslope);
			}

			break;
	}
	return 0;
}

int CVICALLBACK showInfoFunc (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			MessagePopup ("About", "Written for Mechatronics Class");
			break;
	}
	return 0;
}


int CVICALLBACK changeData1 (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int material;
	switch (event)
	{
		case EVENT_COMMIT:
			 GetCtrlVal(panelHandle,PANEL_MATERIAL_OPTIONS_1,&material);
			 SetCtrlAttribute (panelHandle, PANEL_C_BODY_1, ATTR_CTRL_MODE, VAL_INDICATOR);

			 switch (material)
			{
				case 0:
					SetCtrlAttribute (panelHandle, PANEL_C_BODY_1, ATTR_CTRL_MODE, VAL_HOT);
					break;
				case 1:
						SetCtrlVal(panelHandle,PANEL_C_BODY_1,4.186 );
					break;
				case 2:
						SetCtrlVal(panelHandle,PANEL_C_BODY_1,0.900 );
					break;
				case 3:
						SetCtrlVal(panelHandle,PANEL_C_BODY_1, 0.448);
					break;
				case 4:
						SetCtrlVal(panelHandle,PANEL_C_BODY_1, 0.837);
					break;
				case 5:
						SetCtrlVal(panelHandle,PANEL_C_BODY_1, 0.400);
					break;
			}
				
			break;
	}
	return 0;
}

int CVICALLBACK changeData2 (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int material;
	switch (event)
	{
		case EVENT_COMMIT:
			   GetCtrlVal(panelHandle,PANEL_MATERIAL_OPTIONS_2,&material);
			   SetCtrlAttribute (panelHandle, PANEL_C_BODY_2, ATTR_CTRL_MODE, VAL_INDICATOR);
			   
			   switch (material)
			{
				case 0:
					SetCtrlAttribute (panelHandle, PANEL_C_BODY_2, ATTR_CTRL_MODE, VAL_HOT);
					break;
			    case 1:
						SetCtrlVal(panelHandle,PANEL_C_BODY_2,4.186 );
					break;
				case 2:
						SetCtrlVal(panelHandle,PANEL_C_BODY_2,0.900 );
					break;
				case 3:
						SetCtrlVal(panelHandle,PANEL_C_BODY_2, 0.448);
					break;
				case 4:
						SetCtrlVal(panelHandle,PANEL_C_BODY_2, 0.837);
					break;
				case 5:
						SetCtrlVal(panelHandle,PANEL_C_BODY_2, 0.400);
					break;
			}
			break;
	}
	return 0;
}


int CVICALLBACK linkFunc (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			InetLaunchDefaultWebBrowser ("https://www.youtube.com/watch?v=kNZi12OV9Xc");

			break;
	}
	return 0;
}


