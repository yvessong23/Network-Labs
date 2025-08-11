# Network-Labs
This is a repository for my network labs, scenarios, documentation, scripts, and automation

# Hybrid Enterprise Architecture - Zero Trust Security Crisis
**Scenario:** Fortune 500 company's hybrid OSPF/Zero Trust network experiencing critical security and performance failures
**Challenge:** Diagnose and resolve 5 advanced network failures that bypass security controls
**Architecture:** Enterprise design combining OSPF infrastructure with Zero Trust firewall segmentation

## Skills Demonstrated
- Advanced enterprise troubleshooting
- Zero Trust security implementation  
- Policy-Based Routing (PBR)
- Stateful firewall architecture
- OSPF and redundancy design
- Business impact analysis

## Quick Start
[Lab build in progress - full configs coming soon]

## The Architecture
- **Hybrid Design:** OSPF for infrastructure, Zero Trust for user traffic
- **Security Zones:** 5-tier security model with granular policies
- **Advanced Routing:** PBR forcing security inspection
- **Enterprise Scale:** Dual-core redundancy with firewall HA

## The Crisis Scenarios

### 1. Asymmetric Routing Nightmare
- **Impact:** All user sessions dropping randomly
- **Cause:** Stateful firewall losing connection state
- **Business Loss:** Complete application failure

### 2. Security Zone Bypass
- **Impact:** Database directly accessible from app tier
- **Cause:** Rogue SVI bypassing firewall inspection  
- **Business Loss:** Compliance violation, data breach risk

### 3. TCP MSS Black Hole
- **Impact:** Large transactions failing, small ones work
- **Cause:** MTU mismatch through firewall path
- **Business Loss:** Big orders can't complete

### 4. PBR Loop of Death
- **Impact:** Core switches at 100% CPU
- **Cause:** Misconfigured policy routing
- **Business Loss:** Entire network degradation

### 5. DHCP Amplification 
- **Impact:** Users can't connect, IPs exhausted
- **Cause:** Broadcast storm + DHCP relay issue
- **Business Loss:** No new user sessions

## What Makes This Special
- Real-world hybrid architecture
- Security + networking integration
- Multiple failure domains
- Cascading problems that interact
- Demonstrates senior-level thinking
