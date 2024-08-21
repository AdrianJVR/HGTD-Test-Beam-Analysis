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


using namespace ROOT;

double gaussian(double *x, double *par) {
    return par[0]*TMath::Exp(-TMath::Power(x[0] - par[1], 2.) / 2.)
           / TMath::Sqrt(2 * TMath::Pi());
}


int Plots3_DeltaT_Fit()
{

int batch = 4;
int Sensor = 2;

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


int l = 1;
for(int i = p0+4; i< pf-1; i++){
string str1 = "tree_merged_b";
string str2 = to_string(i); 
string str3 = ".root";
string str4 = str1 + str2 + str3;
string str6 = to_string(i);
string str7 = "_fit.pdf";

ROOT::RDataFrame df("tree_combined", str4);

TCanvas *c1 = new TCanvas("c1", "Canvas on which to display our histogram");

auto m1 = df.Define("tcFD_1", "tCFD[0]-tCFD[1]");
auto m2 = m1.Define("tcFD_2", "tCFD[0]-tCFD[2]");

auto m3 = m2.Filter("ntrack==1");

auto m4 = m3;


//Center conditions:


if (batch == 1){
  if(Sensor ==1){
    m4 = m3.Filter("-0.3<LocalX && LocalX<0.0 && -0.05<LocalY && LocalY<0.5 ||-0.5<LocalX && LocalX<-0.2 && 0.6<LocalY && LocalY<1.1 "); //Batch 1. Sensor 1
  }else{
    m4 = m3.Filter("-0.5<LocalX && LocalX<0.5 && -0.2<LocalY && LocalY<0.2"); //Batch 1. Sensor 2
  }
} else if (batch ==2){ 
   if(Sensor ==1){
    m4 = m3.Filter("-1.1<LocalX && LocalX<-0.75 && -0.45<LocalY && LocalY< -0.2|| -0.7<LocalX && LocalX<-0.3 && -0.8<LocalY && LocalY<-0.45"); //Batch 2. Sensor 1
   }else{
    m4 = m3.Filter("-0.4<LocalX && LocalX<0.6 && -0.15<LocalY && LocalY<0.2"); //Batch 2. Sensor 2
  }
} else if (batch == 3){
   if(Sensor ==1){
    m4 = m3.Filter("0.8<LocalX && LocalX<1.2 && 1.3<LocalY && LocalY<1.6 || 0.9<LocalX && LocalX<1.3 && 0.6<LocalY && LocalY<1.2");//Batch 3. Sensor 1
   }else{
    m4 = m3.Filter("-0.5<LocalX && LocalX<0.5 && -0.2<LocalY && LocalY<0.2"); //Batch 3. Sensor 2
  }
} else if(batch == 4){
   if(Sensor ==1){
    m4 = m3.Filter("-0.55<LocalX && LocalX<-0.25 && 0.0<LocalY && LocalY< 0.3 || -0.35<LocalX && LocalX<-0.1 && -0.4<LocalY && LocalY<0.0");//Batch 4. Sensor 1
   }else{
    m4 = m3.Filter("-0.5<LocalX && LocalX<0.5 && -0.2<LocalY && LocalY<0.2"); //Batch 4. Sensor 2
  }
}


//Border Conditions:

/*
auto p0 = m3.Filter("0<Amax[0]<300");
auto p1 = m3.Filter("0<Amax[1]<300");
auto p2 = m3.Filter("0<Amax[2]<300");*/

//auto hist = m3.Histo1D({"MCP-Sensor[3]", "Sensor[1]-Sensor[2] (Batch101)", 200, -1000, 1000}, "tcFD_2");


string str01;
string str010;

if (Sensor == 1){
str01 = "MCP-Sensor[1]";
str010 = "tcFD_1";
} else {
str01 = "MCP-Sensor[2]";
str010 = "tcFD_2";
}


string str5 = "Sensor ";
string str8;
string str9 = ". HV = ";
string str10;

if(Sensor == 1){
   str8 = Sensors[0];
   str10 = Voltage_Sensor1[i-p0];
} else {
   str8 = Sensors[1];
   str10 = Voltage_Sensor2[i-p0];
}

string str11 = str5 + str8 + str9 + str10;

string str02 = " Batch";

const char* title_plot = str11.c_str();
const char* title_leg = str01.c_str();
const char* title_file = str010.c_str();

auto hist = m4.Histo1D({title_leg, title_plot, 300, -9000, -8000}, title_file);
hist->GetXaxis()->SetTitle("#Delta T [ps]");
hist->GetYaxis()->SetTitle("Counts");

string d = title_plot;


//auto hist = ROOT.TH1D(name="h", title="My histo", nbinsx=200, xlow=-200000, xup=200000);

//auto hist = m3.Histo1D({"MCP-Sensor[1]", "MCP-Sensor[1] (Batch101)", 100, -200000, 200000}, "tcFD_0");

//auto fitFunc = new TF1("fitFunc", gaussian, -5, 5, 2);

auto Mean = hist->GetMean();
auto rms = hist->GetRMS();
TF1 *gausFunc = new TF1("gausFunc", "gaus", Mean - 3*rms, Mean + 3*rms);
gausFunc->SetParameter(1,Mean);
gausFunc->SetParameter(2,rms);
for(int i = 0; i<3; i++){
  hist->Fit(gausFunc, "R");
  gausFunc->SetParameter(1,gausFunc->GetParameter(1));
  gausFunc->SetParameter(2,gausFunc->GetParameter(2));
  gausFunc->SetRange(gausFunc->GetParameter(1)-3*gausFunc->GetParameter(2), gausFunc->GetParameter(1)+3*gausFunc->GetParameter(2));
}

float Sigma1 = gausFunc->GetParameter(2);
float MCP_Sigma = 10;
float Sigma1_real = sqrt(pow(Sigma1,2)-pow(MCP_Sigma,2));

std::cout << Sigma1_real << endl;

//res = hist.Fit(fitFunc, "S");

hist->DrawClone();
gausFunc->DrawClone("SAME");

TPaveText *pt = new TPaveText(0.15, 0.7, 0.45, 0.9, "NDC");
pt->SetFillColor(0); // Transparent background
pt->SetTextAlign(12); // Center-align text


pt->AddText("Fit Parameters:");
pt->AddText(Form("Width = %.3f #pm %.3f", gausFunc->GetParameter(0), gausFunc->GetParError(0)));
pt->AddText(Form("MP = %.3f #pm %.3f", gausFunc->GetParameter(1), gausFunc->GetParError(1)));
pt->AddText(Form("GSigma  = %.3f #pm %.3f", gausFunc->GetParameter(2), gausFunc->GetParError(2)));
pt->AddText(Form("#chi^{2} / NDF = %.2f / %d", gausFunc->GetChisquare(), gausFunc->GetNDF()));

pt->DrawClone("SAME"); 

string str12 = ".pdf";
string str14 = "_Batch";
string str13 = str01 + str14 + str2 + str12;

const char* cxx = str13.c_str();

c1->SaveAs(cxx);

string s = cxx;

}

return 0;
}
