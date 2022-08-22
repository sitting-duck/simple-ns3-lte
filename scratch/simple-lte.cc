/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include <ns3/network-module.h>
#include <ns3/mobility-module.h>
#include <ns3/lte-module.h>
#include <ns3/position-allocator.h>
#include "ns3/netanim-module.h"
#include "ns3/flow-monitor-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("simple-lte");

int 
main (int argc, char *argv[])
{
  NS_LOG_UNCOND ("simple-lte");

  std::string animFile = "scratch/animation.xml" ;  // Name of file for animation output
  std::string flowFile = "scratch/flowmonitor.xml" ;  // Name of file for animation output

  // Create LTE Helper Object
  // This will instantiate some common objects (e.g., the Channel object) and provide the methods to add 
  // eNBs (evolved node base stations) and UEs (user equipment) and configure them.
  // User Equipment: is any device used directly by an end-user to communicate. 
  // It can be a hand-held telephone, a laptop computer equipped with a mobile broadband adapter, 
  // or any other device.
  Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();

  // Create Node objects for the eNBs and the UEs
  NodeContainer enbNodes;
  enbNodes.Create(1);     // a base station/cell tower

  NodeContainer ueNodes;
  ueNodes.Create(2);      // 2 cell phones or whatever User Equipment (UE) used to connect to network

  // note that the above Node instances do not have an LTE protocol stack installed; they're just empty nodes

  // Configure the Mobility Model for all the nodes (for moving around the map in space)
  MobilityHelper mobilityEnb;
  Ptr<ListPositionAllocator> positionAllocEnb = CreateObject <ListPositionAllocator>();
  positionAllocEnb->Add(Vector(30, 30, 0)); // node 0


  mobilityEnb.SetPositionAllocator(positionAllocEnb);
  mobilityEnb.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobilityEnb.Install(enbNodes);

  NS_LOG_UNCOND ("Position of base station: " << enbNodes.Get (0)->GetObject<MobilityModel> ()->GetPosition ());

  MobilityHelper mobilityUe;
  Ptr<ListPositionAllocator> positionAllocUe = CreateObject <ListPositionAllocator>();
  positionAllocUe->Add(Vector(10, 10, 0)); // node 0
  positionAllocUe->Add(Vector(20, 20, 0)); // node 1

  mobilityUe.SetPositionAllocator(positionAllocUe);
  mobilityUe.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobilityUe.Install(ueNodes);

  NS_LOG_UNCOND ("boop2");
  NS_LOG_UNCOND ("Position of base station: " << ueNodes.Get (0)->GetObject<MobilityModel> ()->GetPosition ());

  FlowMonitorHelper flowmonHelper;
  flowmonHelper.InstallAll ();

  AnimationInterface anim (animFile);
  anim.EnablePacketMetadata (); // Optional

  Simulator::Run ();
  flowmonHelper.SerializeToXmlFile (flowFile, true, true);
  Simulator::Destroy ();
}
