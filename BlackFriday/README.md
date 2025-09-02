# 🛰️ Network-Labs

This repository contains enterprise-grade **network lab designs, documentation, and automation**.  

---

## 🔒 Hybrid Enterprise Architecture — Zero Trust Security Lab

**Scenario:** Simulated Fortune 500 hybrid OSPF/Zero Trust network.  
**Goal:** Build and test a segmented enterprise network with firewalls, core routing, DHCP/DNS services, and end-to-end policy enforcement.  

---

## 🛠 Skills Demonstrated
- Zero Trust security design and segmentation  
- Stateful firewall configuration (ACLs, NAT, inspection policies)  
- DHCP relay and DNS forwarder integration (*Bind9 on Alpine Linux*)  
- OSPF infrastructure design and troubleshooting  
- Policy-Based Routing (PBR) for security enforcement  
- NAT and double-NAT across firewall/edge layers  
- Enterprise documentation and syslog analysis  

---

## 🏗 The Architecture
- **Hybrid Design:** OSPF for core infrastructure, Zero Trust for user traffic  
- **Security Zones:** 5-tier model *(User, Web, App, DB, Mgmt)*  
- **Advanced Routing:** PBR forcing security inspection before forwarding  
- **Enterprise Scale:** Dual-core switch design with ASA firewall at enforcement points  
- **Visibility:** Syslog, ACL hit-counts, and NAT translation tracking  

---

## 🚨 Crisis Scenarios *(To Be Built Out)*
1. **Asymmetric Routing Nightmare**  
2. **Security Zone Bypass**  
3. **TCP MSS Black Hole**  
4. **PBR Loop of Death**  
5. **DHCP Amplification**  

*(Documented, not yet implemented — these will be added as labs progress.)*  

---

## ✨ What Makes This Special
- Real-world enterprise architecture recreated in **Cisco Modeling Labs (CML)**  
- DNS, DHCP, NAT, and firewall policies integrated with segmentation  
- Layered Zero Trust enforcement with scoped ACLs and least-privilege design  
- Serves as a showcase for **advanced troubleshooting and enterprise thinking**  
