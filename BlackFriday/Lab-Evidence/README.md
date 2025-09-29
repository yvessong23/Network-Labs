# Lab Evidence — BlackFriday Zero Trust Lab

This directory contains the supporting evidence for the BlackFriday Zero Trust Enterprise Lab.  
Each folder documents proof of configuration, security enforcement, and validation tests.  

---

## ASA Firewall

### ACL
- [ACL Hit Count](ASA-Firewall-Screenshots/ACL/acl-hitcount.png)  
  *Proves ACLs are actively matching traffic (User → Web, Web → App, etc.)*  

### NAT
- [NAT Translations](ASA-Firewall-Screenshots/NAT/nat-translations.png)  
  *Demonstrates inside zones translating to the firewall’s outside interface for Internet access.*  

### Packet Tracer (User → Web)
- [Step 1](ASA-Firewall-Screenshots/Packet-Tracer%20USER-WEB/packet-tracer-USER-TO-WEBPT1.png)  
- [Step 2](ASA-Firewall-Screenshots/Packet-Tracer%20USER-WEB/packet-tracer-USER-TO-WEBPT2.png)  
- [Step 3](ASA-Firewall-Screenshots/Packet-Tracer%20USER-WEB/packet-tracer-USER-TO-WEBPT3.png)  
  *Shows ASA packet-tracer confirming allowed flow from User zone to Web server on port 80.*  

### Packet Tracer (Web → App)
- [Step 1](ASA-Firewall-Screenshots/Packet-Tracer%20WEB-APP/packet-tracer-WEB-TO-APP-PT1.png)  
- [Step 2](ASA-Firewall-Screenshots/Packet-Tracer%20WEB-APP/packet-tracer-WEB-TO-APP-PT2.png)  
- [Step 3](ASA-Firewall-Screenshots/Packet-Tracer%20WEB-APP/packet-tracer-WEB-TO-APP-PT3.png)  
  *Validates Web tier can reach App tier, while blocked from skipping directly to DB.*  

---

## Access Switch 1 (User/Web/App)

- [STP Summary](Access-SW1/Access-SW1-Screenshots/02-stp-summary.png)  
- [DHCP Snooping](Access-SW1/Access-SW1-Screenshots/show-dhcp-snooping.png)  
- [Interface Trunks](Access-SW1/Access-SW1-Screenshots/show-interface-trunk.png)  
- [Port Security](Access-SW1/Access-SW1-Screenshots/show-port-security.png)  
- [VLANs](Access-SW1/Access-SW1-Screenshots/show-vlan-brief-asw1.png)  

*Demonstrates L2 security and segmentation at the access layer.*  

---

## Access Switch 2 (DB/Mgmt)

- [Trunk Config](Access-SW2/Access-SW2-Screenshots/show-interfaces-trunk.png)  
- [DHCP Snooping](Access-SW2/Access-SW2-Screenshots/show-ip-dhcp-snooping.png)  
- [Port Security](Access-SW2/Access-SW2-Screenshots/show-port-security.png)  
- [STP Summary](Access-SW2/Access-SW2-Screenshots/show-spanning-tree-summary.png)  
- [VLANs](Access-SW2/Access-SW2-Screenshots/show-vlan-brief.png)  

*Confirms isolation of DB/Mgmt VLANs and enforcement at L2.*  

---

## Servers

### App Server
- [API Running](Servers/APP/app-running-api-created.png)  
  *Flask API responding to requests, backed by DB.*  

### Database Server
- [Schema](Servers/DB/DB/db-schema.png)  
- [psql Output](Servers/DB/DB/psql-format-db.png)  
  *Shows database schema powering bookings API.*  

### DNS (Mgmt Server)
- [Client to Google DNS](Servers/MGMT-DNS/client-to-google-dns.png)  
- [DIG Test](Servers/MGMT-DNS/dig-to-google.png)  
- [netstat](Servers/MGMT-DNS/netstat-dns.png)  
  *Validates DNS resolution via local management server.*  

### Web Server
- [Client to Web](Servers/WEB/client-to-web-server.png)  
- [Reverse Proxy Works](Servers/WEB/reverse-proxy-works.png)  
- [Access Logs](Servers/WEB/web-access-log-port-listen.png)  
- [Web Logs](Servers/WEB/web-server-access-log.png)  
  *Nginx serving homepage and forwarding API traffic to App.*  

---

## Topology

- [CML Topology](Topology/cml-topology.png)  
- [Draw.io Topology](Topology/BlackFriday.drawio.png)  

*Visual reference of lab layout.*  
