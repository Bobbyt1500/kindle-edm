#include "XPLMPlugin.h"
#include "XPLMProcessing.h"
#include "XPLMDataAccess.h"
#include <windows.h>
#include <sstream> 
#include <iomanip>


#ifndef XPLM300
	#error This is made to be compiled against the XPLM300 SDK
#endif

HANDLE hMapFile;
LPVOID pBuf;

static float FlightLoopCallback(
	float                inElapsedSinceLastCall,    
    float                inElapsedTimeSinceLastFlightLoop,    
    int                  inCounter,    
    void *               inRefcon);

XPLMDataRef RPMs;
XPLMDataRef MPRs;
XPLMDataRef CHTs;
XPLMDataRef EGTs;
XPLMDataRef OILPs;
XPLMDataRef OILTs;
XPLMDataRef FUELFs;
XPLMDataRef FUELPs;
XPLMDataRef LFUEL;
XPLMDataRef RFUEL;
XPLMDataRef VOLTs;
XPLMDataRef AMPs;
XPLMDataRef OAT;
XPLMDataRef AVON;
XPLMDataRef BATON;

PLUGIN_API int XPluginStart(
							char *		outName,
							char *		outSig,
							char *		outDesc)
{
	strcpy(outName, "KindleEDMPlugin");
	strcpy(outSig, "bthierry.kindleedm");
	strcpy(outDesc, "An engine monitoring display for X-Plane 11");

	RPMs = XPLMFindDataRef("sim/cockpit2/engine/indicators/prop_speed_rpm");
	MPRs = XPLMFindDataRef("sim/cockpit2/engine/indicators/MPR_in_hg");
	CHTs = XPLMFindDataRef("sim/cockpit2/engine/indicators/CHT_deg_C");
	EGTs = XPLMFindDataRef("sim/cockpit2/engine/indicators/EGT_deg_C");
	OILPs = XPLMFindDataRef("sim/cockpit2/engine/indicators/oil_pressure_psi");
	OILTs = XPLMFindDataRef("sim/cockpit2/engine/indicators/oil_temperature_deg_C");
	FUELFs = XPLMFindDataRef("sim/cockpit2/engine/indicators/fuel_flow_kg_sec");
	FUELPs = XPLMFindDataRef("sim/cockpit2/engine/indicators/fuel_pressure_psi");
	LFUEL = XPLMFindDataRef("sim/cockpit2/fuel/fuel_level_indicated_left");
	RFUEL = XPLMFindDataRef("sim/cockpit2/fuel/fuel_level_indicated_right");
	VOLTs = XPLMFindDataRef("sim/cockpit2/electrical/battery_voltage_indicated_volts");
	AMPs = XPLMFindDataRef("sim/cockpit2/electrical/bus_load_amps");
	OAT = XPLMFindDataRef("sim/cockpit2/temperature/outside_air_temp_degf");
	AVON = XPLMFindDataRef("sim/cockpit/electrical/avionics_on");
	BATON = XPLMFindDataRef("sim/cockpit/electrical/battery_on");

	hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MAX_PATH, "KindleEDMFile");
    pBuf = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, MAX_PATH);

	XPLMRegisterFlightLoopCallback(		
		FlightLoopCallback,	/* Callback */
		0.1,					/* Interval */
		NULL);					/* refcon not used. */

	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
	UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);

	XPLMUnregisterFlightLoopCallback(FlightLoopCallback, NULL);
}

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void)  { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam) { }

static float FlightLoopCallback(
	float                inElapsedSinceLastCall,    
    float                inElapsedTimeSinceLastFlightLoop,    
    int                  inCounter,    
    void *               inRefcon) {

	float rpm_datas[8];
	float mpr_datas[8];
	float cht_datas[8];
	float egt_datas[8];
	float oilp_datas[8];
	float oilt_datas[8];
	float fuelf_datas[8];
	float fuelp_datas[8];
	float volt_datas[8];
	float amp_datas[8];
	float fuelL_data;
	float fuelR_data;
	float oat_data;
	int avon_data;
	int baton_data;
	XPLMGetDatavf(RPMs, rpm_datas, 0, 8);
	XPLMGetDatavf(MPRs, mpr_datas, 0, 8);
	XPLMGetDatavf(CHTs, cht_datas, 0, 8);
	XPLMGetDatavf(EGTs, egt_datas, 0, 8);
	XPLMGetDatavf(OILPs, oilp_datas, 0, 8);
	XPLMGetDatavf(OILTs, oilt_datas, 0, 8);
	XPLMGetDatavf(FUELFs, fuelf_datas, 0, 8);
	XPLMGetDatavf(FUELPs, fuelp_datas, 0, 8);
	XPLMGetDatavf(VOLTs, volt_datas, 0, 8);
	XPLMGetDatavf(AMPs, amp_datas, 0, 8);
	fuelL_data = XPLMGetDataf(LFUEL);
	fuelR_data = XPLMGetDataf(RFUEL);
	oat_data = XPLMGetDataf(OAT);
	avon_data = XPLMGetDatai(AVON);
	baton_data = XPLMGetDatai(BATON);

	// Convert Fuel flow from KG/s to GPH
	fuelf_datas[0] *= 1296;

	// Convert fuel quantities from KGs to Gallons
	fuelL_data *= 0.36;
	fuelR_data *= 0.36;
	std::stringstream str;

	str << std::fixed << std::setprecision(0) << rpm_datas[0] << ',' << std::setprecision(1) << mpr_datas[0] << ',' << std::setprecision(0) << cht_datas[0] << ',' << egt_datas[0] << ','
		<< oilp_datas[0] << ',' << oilt_datas[0] << ',' << fuelL_data << ',' << fuelR_data << ',' << std::setprecision(1) << fuelf_datas[0] << ','
		<< volt_datas[0] << ',' << std::setprecision(0) << amp_datas[0] << ',' << fuelp_datas[0] << ',' << oat_data << ',' << ((avon_data == 1 && baton_data == 1) ? 1 : 0) << ',';

	FlushViewOfFile(pBuf, 0);
	memcpy(pBuf, str.str().c_str(), strlen(str.str().c_str()) * sizeof(char));

	return 0.1;
}
