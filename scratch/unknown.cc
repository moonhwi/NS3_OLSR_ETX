#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/olsr-helper.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/flow-classifier.h"
#include "ns3/ipv4-flow-classifier.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/spectrum-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("SimplePointToPointOlsrExample");

int main(int argc, char *argv[])
{

    // Set up some default values for the simulation.  Use the

    Config::SetDefault("ns3::OnOffApplication::PacketSize", UintegerValue(210));
    Config::SetDefault("ns3::OnOffApplication::DataRate", StringValue("1000kb/s"));
    uint32_t nWifi = 4;

    //DefaultValue::Bind ("DropTailQueue::m_maxPackets", 30);

    // Allow the user to override any of the defaults and the above
    // DefaultValue::Bind ()s at run-time, via command-line arguments
    CommandLine cmd;
    cmd.Parse(argc, argv);
    cmd.AddValue("nWifi", "Number of wifi STA devices", nWifi);

    // Here, we will explicitly create four nodes.  In more sophisticated
    // topologies, we could configure a node factory.
    NS_LOG_INFO("Create nodes.");
    NodeContainer c;
    c.Create(nWifi);
    SpectrumWifiPhyHelper spectrumPhy;
    Ptr<MultiModelSpectrumChannel> spectrumChannel;
    spectrumChannel = CreateObject<MultiModelSpectrumChannel>();
    Ptr<FriisPropagationLossModel> lossModel = CreateObject<FriisPropagationLossModel>();
    lossModel->SetFrequency(5.180e9);
    spectrumChannel->AddPropagationLossModel(lossModel);
    Ptr<ConstantSpeedPropagationDelayModel> delayModel = CreateObject<ConstantSpeedPropagationDelayModel>();
    spectrumChannel->SetPropagationDelayModel(delayModel);
    spectrumPhy.SetChannel(spectrumChannel);
    spectrumPhy.SetErrorRateModel("ns3::NistErrorRateModel");
    spectrumPhy.Set("Frequency", UintegerValue(5180)); // channel 36 at 20 MHz
    WifiHelper wifi;
    wifi.SetStandard(WifiStandard::WIFI_STANDARD_80211n_5GHZ);
    wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager", "DataMode", StringValue("OfdmRate54Mbps"), "ControlMode", StringValue("OfdmRate54Mbps"));
    WifiMacHelper mac;
    mac.SetType("ns3::AdhocWifiMac");

    NetDeviceContainer wifidevice1;
    wifidevice1 = wifi.Install(spectrumPhy, mac, c);
    MobilityHelper mobility;

    mobility.SetPositionAllocator("ns3::GridPositionAllocator", //网格位置分配器
                                  "MinX", DoubleValue(0.0),
                                  "MinY", DoubleValue(0.0),
                                  "DeltaX", DoubleValue(1.0),
                                  "DeltaY", DoubleValue(1.0),
                                  "GridWidth", UintegerValue(2),
                                  "LayoutType", StringValue("RowFirst"));

    //   mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel", //以随机游走的方式移动
    //                              "Bounds", RectangleValue (Rectangle (-50, 50, -50, 50)));
    mobility.InstallAll(); //安装到wifi网络的ST
    //mobility.Install(c);

    OlsrHelper olsr;
    //list.Add(olsr,0);
    //Ipv4StaticRoutingHelper staticRouting;

    //Ipv4ListRoutingHelper list;
    //list.Add (staticRouting, 0);
    //list.Add (olsr, 10);

    InternetStackHelper internet;
    internet.SetRoutingHelper(olsr); // has effect on the next Install ()
    //internet.Install (c);
    internet.InstallAll();

    Ipv4AddressHelper address;
    address.SetBase("195.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer Satip_2 = address.Assign(wifidevice1);

    OnOffHelper onOff1("ns3::UdpSocketFactory", Address(InetSocketAddress(Satip_2.GetAddress(0), 9)));
    onOff1.SetConstantRate(DataRate("0.8Mbps"));
    //Config::SetDefault("ns3::OnOffApplication::PacketSize", UintegerValue(2000));
    // Config::SetDefault("ns3::OnOffApplication::DataRate", StringValue("2Mbps"));
    // onOff1.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=0.5]"));
    // onOff1.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0.5]"));
    ApplicationContainer apps1 = onOff1.Install(c.Get(3));
    apps1.Start(Seconds(10.0));
    apps1.Stop(Seconds(20.0));

    // OnOffHelper onOff2("ns3::UdpSocketFactory", Address(InetSocketAddress(Satip_2.GetAddress(1), 9)));
    // onOff2.SetConstantRate (DataRate ("0.8Mbps"));
    // Config::SetDefault("ns3::OnOffApplication::PacketSize", UintegerValue(2000));
    // Config::SetDefault("ns3::OnOffApplication::DataRate", StringValue("2Mbps"));
    // onOff1.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=0.5]"));
    // onOff1.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0.5]"));
    // ApplicationContainer apps2 = onOff2.Install(c.Get(0));
    // apps2.Start(Seconds(10.1));
    // apps2.Stop(Seconds(20.0));

    FlowMonitorHelper flowmonHelper;
    Ptr<FlowMonitor> monitor = flowmonHelper.InstallAll();

    // Ipv4GlobalRoutingHelper k;
    // Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper>("/home/limenghui/Downloads/ns-allinone-3.30.1/ns-3.30.1/SATDATA/Olsrouting3.routes", std::ios::out);
    // k.PrintRoutingTableAllEvery(Seconds(3), routingStream);
    Simulator::Stop(Seconds(30));

    NS_LOG_UNCOND("Run Simulation.");
    Simulator::Run();
    monitor->CheckForLostPackets();
    Ptr<Ipv4FlowClassifier> classifier =
        DynamicCast<Ipv4FlowClassifier>(flowmonHelper.GetClassifier());
    std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats();
    for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin();
         i != stats.end(); ++i)
    {
        Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(i->first);
        std::cout << "Flow " << i->first << " (" << t.sourceAddress << " -> " << t.destinationAddress
                  << ")\n";
        std::cout << "  Tx Packets:   " << i->second.txPackets << "\n";
        std::cout << "  Rx Packets:   " << i->second.rxPackets << "\n";
        std::cout << "  last Delay:   " << i->second.lastDelay.GetSeconds() << "\n";
        std::cout << "  delay: " << i->second.delaySum.GetSeconds() / i->second.rxPackets << " s\n";
        std::cout << "  lostpackets: " << i->second.lostPackets << " \n";
        std::cout << "  Throughput: "
                  << i->second.rxBytes * 8.0 /
                         (i->second.timeLastRxPacket.GetSeconds() -
                          i->second.timeFirstRxPacket.GetSeconds()) /
                         1024 / 1024
                  << " Mbps\n";
    }
    Simulator::Destroy();
    NS_LOG_INFO("Done.");

    return 0;
}