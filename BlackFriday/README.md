# 🛰️ Network-Labs

Zero Trust network architecture, built at home from scratch. Every lab is a step toward designing networks at the scale of Fortune 500 enterprises. Documented with configs, diagrams, and crisis scenarios. 

---

## 🔒 Hybrid Enterprise Architecture — Zero Trust Security Lab

**Scenario:** Simulated Fortune 500 hybrid OSPF/Zero Trust network.  
**Goal:** Build and test a segmented enterprise network with firewalls, core routing, DHCP/DNS services, and end-to-end policy enforcement.  

---

## 🛠 Skills Demonstrated
Zero Trust segmentation → the philosophy.

Firewall enforcement (ACLs, NAT, inspection) → the guardrails.

DNS/DHCP resilience → the foundation no one talks about.

OSPF + PBR → advanced routing for security inspection.

Visibility → syslog, ACL counters, NAT debugging.

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
**I built this lab because I believe the network is the first defense of cyber. Every config, every ACL, every NAT rule has a why. This isn’t just practice — it’s preparation for the day I’m the one designing real enterprise networks.**
