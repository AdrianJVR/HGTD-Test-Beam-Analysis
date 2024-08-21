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

int Plots9_Borders_DeltaT_Fit()
{

using namespace ROOT;

int batch = 1;
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

const int S1i = -9000;
const int S2i = -9000;
const int S1f = -8000;
const int S2f = -8000;

string str6 = to_string(batch);
string str7 = ".pdf";

TCanvas *c3 = new TCanvas("c3", "Canvas on which to display our histogram");

auto legend2 = new TLegend(0.5,0.8,0.6,0.9);
legend2->SetHeader("Batches","C");
int l = 1;
for(int i = p0+4; i< pf-0; i++){
string str1 = "tree_merged_b";
string str2 = to_string(i);
string str3 = ".root";
string str4 = str1 + str2 + str3;



ROOT::RDataFrame df("tree_combined", str4);

auto m = df.Filter("ntrack==1");
auto m02 = m.Define("tcFD_2", "tCFD[0]-tCFD[2]");
auto n2 = m02.Filter("tcFD_2");

auto m2 = n2;


//Cuts to apply
if (batch ==1){

//Borders:
//m2 = n2.Filter("-1.1 < LocalX && LocalX < 1.0 && -0.4 < LocalY  && LocalY < -0.21 || -1.1 < LocalX && LocalX < -0.98 && -0.21 < LocalY && LocalY < 0.25 || -1.1 < LocalX && LocalX < 1.0 && 0.25 < LocalY && LocalY < 0.4 || 0.89 < LocalX && LocalX < 1.0 && -0.21 < LocalY && LocalY < 0.25");
//m2 = n2.Filter("-1.1 < LocalX && LocalX < 1.0 && -0.4 < LocalY && LocalY  < -0.21 || -1.1 < LocalX && LocalX < 1.0 && 0.25 < LocalY && LocalY < 0.4 || -1.1 < LocalX && LocalX < -0.97 && -0.21 < LocalY && LocalY < 0.25 || 0.88 < LocalX && LocalX < 1.0 && -0.21 < LocalY && LocalY < 0.25"); //Batch 101. Sensor 2
//m2 = n2.Filter("-1.1 < LocalX && LocalX < 1.0 && -0.4 < LocalY && LocalY < -0.21 || -1.1 < LocalX && LocalX < 1.0 && 0.21 < LocalY && LocalY < 0.4 || -1.1 < LocalX && LocalX < -0.95 && -0.21 < LocalY && LocalY < 0.21 || 0.86 < LocalX && LocalX < 1.0 && -0.21 < LocalY && LocalY < 0.21"); //Batch 102. Sensor 2
//m2 = n2.Filter("-1.1 < LocalX && LocalX < 1.0 && -0.4 < LocalY && LocalY < -0.2 || -1.1 < LocalX && LocalX < 1.0 && 0.2 < LocalY && LocalY < 0.4 || -1.1 < LocalX && LocalX < -0.99 && -0.2 < LocalY && LocalY < 0.2 || 0.88 < LocalX && LocalX < 1.0 && -0.2 < LocalY && LocalY < 0.2"); //Batch 103. Sensor 2
//m2 = n2.Filter("-1.1 < LocalX && LocalX < 1.0 && -0.37 < LocalY && LocalY < -0.2 || -1.1 < LocalX && LocalX < 1.0 && 0.2 < LocalY && LocalY < 0.4 || -1.1 < LocalX && LocalX < -0.96 && -0.2 < LocalY && LocalY < 0.2 || 0.85 < LocalX && LocalX < 1.0 && -0.2 < LocalY && LocalY < 0.2"); //Batch 104. Sensor 2

//Total:

//m2 = n2.Filter("-1.1 < LocalX && LocalX < 1.0 && -0.4 < LocalY && LocalY < 0.4"); //Batch 100. Sensor 2
//m2 = n2.Filter("-1.1 < LocalX && LocalX < 1.0 && -0.4 < LocalY && LocalY < 0.4"); //Batch 101. Sensor 2
//m2 = n2.Filter("-1.1 < LocalX && LocalX < 1.0 && -0.38 < LocalY && LocalY < 0.4"); //Batch 102. Sensor 2
//m2 = n2.Filter("-1.1 < LocalX && LocalX < 1.0 && -0.4 < LocalY && LocalY < 0.4"); //Batch 103. Sensor 2
m2 = n2.Filter("-1.1 < LocalX && LocalX < 1.0 && -0.37 < LocalY && LocalY < 0.4"); //Batch 104. Sensor 2


} else if (batch ==2){

m2 = n2.Filter("-0.8 < LocalX < 1.2 && -0.28 < LocalY < -0.1 || -0.8 < LocalX < 1.2 && 0.2 < LocalY < 0.38 ||-0.8 < LocalX < -0.68 && -0.1 < LocalY < 0.2 || 1.05 < LocalX < 1.2 && -0.1 < LocalY < 0.2"); //Batch 200. Sensor 2

//m2 = n2.Filter("-0.8 < LocalX < 1.2 && -0.3 < LocalY < 0.15 ||-0.8 < LocalX < 1.2 && 0.25 < LocalY < 0.4 ||-0.8 < LocalX < -0.7 && -0.15 < LocalY < 0.25 ||1.1 < LocalX < 1.2 && -0.15 < LocalY < 0.25 "); //Batch 204. Sensor 2

} else if (batch == 3){

m2 = n2.Filter("-1.0 < LocalX < 1.0 && -0.35 < LocalY < -0.2 ||-1.0 < LocalX < 1.0 && 0.2 < LocalY < 0.35 ||-1.0 < LocalX < -0.87 && -0.2 < LocalY < 0.2 ||0.87 < LocalX < 1.0 && -0.2 < LocalY < 0.2"); //Batch 304. Sensor 2

} else if (batch == 4){

m2 = n2.Filter("-0.92 < LocalX < 1.02 && 0.2 < LocalY < 0.35 ||-0.92 < LocalX < 1.02 && -0.3 < LocalY < -0.2 ||-0.92 < LocalX < -0.85 && -0.2 < LocalY < 0.2 ||0.92 < LocalX < 1.02 && -0.2 < LocalY < 0.2 "); //Batch 404. Sensor 2

} 
//End of the cuts to apply


string str01 = "Delta T [ps] Sensor 2";
string str02 = " Batch ";
string str03 = str01 + str02 + to_string(batch);
const char* title_real = str03.c_str();

auto h2 = m2.Histo1D({"ΔT Sensor 2", title_real, 300, S2i, S2f}, "tcFD_2"); 
h2->GetXaxis()->SetTitle("#Delta T [ps]");
h2->GetYaxis()->SetTitle("Counts");


h2->SetLineColor(l);

auto Mean = h2->GetMean();
auto rms = h2->GetRMS();
TF1 *gausFunc = new TF1("gausFunc", "gaus", Mean - 3*rms, Mean + 3*rms);
gausFunc->SetParameter(1,Mean);
gausFunc->SetParameter(2,rms);
gausFunc->SetParLimits(2,0,4*rms);
for(int i = 0; i<3; i++){
  //gausFunc->SetParLimits(2,0,4*rms);
  h2->Fit(gausFunc, "R");
  gausFunc->SetParameter(1,gausFunc->GetParameter(1));
  gausFunc->SetParameter(2,gausFunc->GetParameter(2));
  gausFunc->SetRange(gausFunc->GetParameter(1)-3*gausFunc->GetParameter(2), gausFunc->GetParameter(1)+3*gausFunc->GetParameter(2));
  gausFunc->SetParLimits(2,0,4*gausFunc->GetParameter(2));
}

float Sigma2 = gausFunc->GetParameter(2);
float MCP_Sigma = 10.;
float Sigma2_real = sqrt(pow(Sigma2,2)-pow(MCP_Sigma,2));

std::cout<< "Sigma for sensor: " << Sigma2_real << endl;


const char* str2_const = str2.c_str();
TLegendEntry* l0 = legend2->AddEntry("h2", str2_const, "l");
l0->SetTextColor(l);
string s = str2;
h2->DrawClone();
gausFunc->DrawClone("SAME");
l++;
}
legend2->Draw("SAME");

string str11 = "ΔT_2_Batch";
string str12 = str11 + str6 + str7;

const char* cxz = str12.c_str();

c3->SaveAs(cxz);

return 0; 
}

//auto m02 = df.Define("tcFD_1", "tCFD[0]-tCFD[1]");
