#include "ROOT/InternalTreeUtils.hxx"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RDataSource.hxx"
#include "ROOT/RDF/RDatasetSpec.hxx"
#include "ROOT/RDF/RInterface.hxx"
#include "ROOT/RDF/RLoopManager.hxx"
#include "ROOT/RDF/Utils.hxx"
#include <string_view>
#include "TChain.h"
#include "TDirectory.h"
#include "RtypesCore.h" // for ULong64_t
#include "TTree.h"
#include "ROOT/RVec.hxx"
#include "TLegend.h"
#include <list>
#include <iostream>
#include <vector>
#include <string>
#include <TFile.h>
#include <array>

int Plots2_2DEff()
{
gStyle->SetOptStat(0);
using namespace ROOT;

ROOT::EnableImplicitMT();

int batch = 4;
int sensor = 2;

int p0, pf;

std::vector <string> Voltage_Sensor1;
std::vector <string> Voltage_Sensor2;
std::vector <string> Sensors;

if (batch == 1){
//batch 1

Voltage_Sensor1.push_back("107 V");
Voltage_Sensor1.push_back("112 V"); 
Voltage_Sensor1.push_back("117 V"); 
Voltage_Sensor1.push_back("122 V");
Voltage_Sensor1.push_back("127 V");
Sensors.push_back("USTC W7P50 0E14"); 

Voltage_Sensor2.push_back("130 V"); 
Voltage_Sensor2.push_back("135 V");
Voltage_Sensor2.push_back("140 V");
Voltage_Sensor2.push_back("145 V"); 
Voltage_Sensor2.push_back("150 V"); 
Sensors.push_back("IHEP W10P51 0E14"); 

p0 = batch*100;
pf = p0 + 5;
} else if (batch ==2){ 
 //Batch2
 
Voltage_Sensor1.push_back("125 V");
Voltage_Sensor1.push_back("128 V"); 
Voltage_Sensor1.push_back("131 V");
Voltage_Sensor1.push_back("134 V");
Voltage_Sensor1.push_back("137 V");
Voltage_Sensor1.push_back("140 V"); 
Sensors.push_back("IHEP W16p43 0E14"); 

Voltage_Sensor2.push_back("300 V");
Voltage_Sensor2.push_back("330 V"); 
Voltage_Sensor2.push_back("360 V");
Voltage_Sensor2.push_back("390 V");
Voltage_Sensor2.push_back("420 V");
Voltage_Sensor2.push_back("450 V");
Sensors.push_back("IHEP W16P52 15E14"); 

p0 = batch*100;
pf = p0 + 6;
} else if (batch == 3){
//Batch3

Voltage_Sensor1.push_back("455 V");
Voltage_Sensor1.push_back("480 V");
Voltage_Sensor1.push_back("505 V");
Voltage_Sensor1.push_back("530 V");
Voltage_Sensor1.push_back("555 V");
Voltage_Sensor1.push_back("580 V"); 
Sensors.push_back("USTC W15P49 25E14"); 

Voltage_Sensor2.push_back("455 V");
Voltage_Sensor2.push_back("480 V");
Voltage_Sensor2.push_back("505 V");
Voltage_Sensor2.push_back("530 V");
Voltage_Sensor2.push_back("555 V");
Voltage_Sensor2.push_back("580 V");
Sensors.push_back("IHEP W16P49 25E14"); 

p0 = batch*100;
pf = p0 + 6;
} else if(batch == 4){
//Batch4

Voltage_Sensor1.push_back("455 V");
Voltage_Sensor1.push_back("480 V");
Voltage_Sensor1.push_back("505 V");
Voltage_Sensor1.push_back("530 V");
Voltage_Sensor1.push_back("555 V");
Voltage_Sensor1.push_back("580 V"); 
Sensors.push_back("USTC W15P1 25E14"); 

Voltage_Sensor2.push_back("455 V");
Voltage_Sensor2.push_back("480 V");
Voltage_Sensor2.push_back("505 V");
Voltage_Sensor2.push_back("530 V");
Voltage_Sensor2.push_back("555 V");
Voltage_Sensor2.push_back("580 V");
Sensors.push_back("IHEP W10P49 25E14"); 

p0 = batch*100;
pf = p0 + 6; 
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TCanvas *c1 = new TCanvas("c1", "Canvas on which to display our histogram");
for(int i = p0+4; i< pf-1; i++){

string str1 = "tree_merged_b";
string str2 = to_string(i);
string str3 = ".root";
string str4 = str1 + str2 + str3;

ROOT::RDataFrame df("tree_combined", str4);

TCanvas *c1 = new TCanvas("c1", "Canvas on which to display our histogram");

auto m = df.Filter("ntrack==1");
m = m.Define("charge_0", "charge[0]");
m = m.Define("charge_1", "charge[1]");
m = m.Define("charge_2", "charge[2]");

auto h = m.Histo2D({"Histo2D", "Histo2D", 100, -2.5, 2.5, 100, -2.5, 2.5},"LocalX", "LocalY");

//auto m0 = m.Filter("4<charge[0]");
//auto m1 = m.Filter("4<charge[1]");

auto m2 = m;

string str5 = "Sensor ";
string str6;
string str7 = ". HV = ";
string str8;

if(sensor == 1){
   m2 = m.Filter("charge_1>4");
   str6 = Sensors[0];
   str8 = Voltage_Sensor1[i-p0];
} else {
   m2 = m.Filter("charge_2>4");
   str6 = Sensors[1];
   str8 = Voltage_Sensor2[i-p0];
}

string str9 = str5 + str6 + str7 + str8;

const char* cxx0 = str9.c_str();

/*
auto h0 = m0.Histo2D({"Histo2D_0", cxx0, 100, -2.5, 2.5, 100, -2.5, 2.5},"LocalX", "LocalY");
h0->Divide(h.GetPtr());
h0->Draw("colz");
c1->SaveAs("2DPlot_chargeEff_0");

string str9 = str6 + str2;

const char* cxx1 = str9.c_str();

auto h1 = m1.Histo2D({"Histo2D_1", cxx1, 100, -2.5, 2.5, 100, -2.5, 2.5}, "LocalX", "LocalY");

h1->Divide(h.GetPtr());
h1->Draw("colz");

c1->SaveAs("2DPlot_chargeEff_1");
*/
//string str8 = str6 + str2;

//const char* cxx2 = str10.c_str();

auto h2 = m2.Histo2D({"Histo2D_2", cxx0, 100, -2.5, 2.5, 100, -2.5, 2.5}, "LocalX", "LocalY");
h2->Divide(h.GetPtr());
h2->GetXaxis()->SetTitle("LocalX [mm]");
h2->GetYaxis()->SetTitle("LocalY [mm]");

string s = str9;
h2->Draw("colz");
//legend1->Draw("SAME");

string str10 = "Efficiency 2DPlot Batch ";
string str11 = " Sensor "; 
string str12 = to_string(sensor);
string str13 = ".pdf";
string str14 = str10 + str2 + str11 + str12 + str13;

const char* cxx = str14.c_str();

c1->SaveAs(cxx);

}

return 0;
}




















