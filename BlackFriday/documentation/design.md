## VLAN Table

| **VLAN ID** | **Name**           | **Purpose**                   | **Subnet**       | **Gateway**  | **Notes**                  |
|-------------|-------------------|--------------------------------|------------------|--------------|----------------------------|
| 10          | WEB-ZONE          | Public web servers            | 10.100.0.0/24    | 10.100.0.1   | nginx test server (PC1)    |
| 20          | APP-ZONE          | Application servers           | 10.200.0.0/24    | 10.200.0.1   | Flask app server (PC2)     |
| 30          | DB-ZONE           | Database servers              | 10.30.0.0/24     | 10.30.0.1    | PostgreSQL server (PC3)    |
| 50          | USER-ZONE         | End-user clients              | 10.40.0.0/24     | 10.40.0.1    | DHCP pool for PC4 & PC5    |
| 99          | MGMT-ZONE         | Infrastructure management     | 10.99.0.0/24     | 10.99.0.1    | Mgmt IPs for infra devices |
| 999         | NATIVE-BLACKHOLE  | Disabled native VLAN (security)| —                | —            | Shut down, no ports        |


## Switchport Assignments

| **Switch**   | **Interface** | **VLAN** | **Mode** | **Connected Device**   |
|--------------|--------------|----------|----------|------------------------|
| Access-SW1   | E0           | 10       | Access   | PC1 (nginx server)     |
| Access-SW1   | E1           | 20       | Access   | PC2 (Flask app server) |
| Access-SW1   | E2           | 50       | Access   | PC5 (Client)           |
| Access-SW2   | E0           | 30       | Access   | PC3 (PostgreSQL DB)    |
| Access-SW2   | E1           | 50       | Access   | PC4 (Client)           |


## Trunk Links

| **From Device** | **From Interface** | **To Device** | **To Interface** | **Native VLAN** | **Allowed VLANs**         |
|-----------------|--------------------|---------------|------------------|-----------------|---------------------------|
| CoreSW1         | G0/1               | Firewall      | G0/1             | 999             | 10,20,30,50,99,999         |
| CoreSW2         | G0/1               | Firewall      | G0/2             | 999             | 10,20,30,50,99,999         |
| CoreSW1         | G0/0               | CoreSW2       | G0/0             | 999             | 99,999 (Infra OSPF only)   |
| CoreSW1         | GiX/X (example)    | Access-SW1    | GiX/X             | 999             | 10,20,50,99,999            |
| CoreSW2         | GiX/X (example)    | Access-SW2    | GiX/X             | 999             | 30,50,99,999               |


## IP Addressing – Per Device

### INET-EDGE Router
| **Interface** | **IP Address / Prefix** | **Purpose / Notes**        |
|---------------|-------------------------|----------------------------|
| G0/0          | 203.0.113.1 /30         | Internet gateway toward ISP |

---

## OSPF Design

| **Neighbor 1** | **Neighbor 2** | **Link Subnet** | **Area** | **Purpose**                | **Auth** |
|----------------|----------------|-----------------|----------|----------------------------|----------|
| CoreSW1 (G0/0) | CoreSW2 (G0/0) | 10.1.1.0/30     | 0        | Core interconnect           | None     |
| CoreSW1 (VLAN99 SVI) | Firewall (VLAN99) | 10.99.0.0/24 | 0 | Mgmt reachability (optional) | None     |


### Firewall-Primary
| **Interface**   | **IP Address / Prefix** | **VLAN / Zone** | **Purpose / Notes**         |
|-----------------|-------------------------|-----------------|-----------------------------|
| G0/0 (outside)  | 203.0.113.2 /30         | —               | Outside to edge router      |
| G0/1.10         | 10.100.0.1 /24          | VLAN 10 – WEB   | Gateway for WEB-ZONE        |
| G0/1.20         | 10.200.0.1 /24          | VLAN 20 – APP   | Gateway for APP-ZONE        |
| G0/1.30         | 10.30.0.1 /24           | VLAN 30 – DB    | Gateway for DB-ZONE         |
| G0/1.50         | 10.40.0.1 /24           | VLAN 50 – USER  | Gateway for USER-ZONE       |
| G0/1.99         | 10.99.0.1 /24           | VLAN 99 – MGMT  | Gateway for MGMT-ZONE       |

---

### CoreSW1
| **Interface** | **IP Address / Prefix** | **VLAN / Network** | **Purpose / Notes**        |
|---------------|-------------------------|--------------------|----------------------------|
| G0/0          | 10.1.1.1 /30            | Infra link to CoreSW2 | OSPF Area 0 peer         |
| VLAN 99 (SVI) | 10.99.0.2 /24            | MGMT-ZONE          | Mgmt IP for infra control  |

---

### CoreSW2
| **Interface** | **IP Address / Prefix** | **VLAN / Network** | **Purpose / Notes**        |
|---------------|-------------------------|--------------------|----------------------------|
| G0/0          | 10.1.1.2 /30            | Infra link to CoreSW1 | OSPF Area 0 peer         |
| VLAN 99 (SVI) | 10.99.0.3 /24            | MGMT-ZONE          | Mgmt IP for infra control  |

---

### PC-WEB (PC1)
| **Interface** | **IP Address / Prefix** | **VLAN / Zone** | **Purpose / Notes**   |
|---------------|-------------------------|-----------------|-----------------------|
| E0            | 10.100.0.10 /24         | VLAN 10 – WEB   | nginx web server      |

---

### PC2 (APP)
| **Interface** | **IP Address / Prefix** | **VLAN / Zone** | **Purpose / Notes**     |
|---------------|-------------------------|-----------------|-------------------------|
| E0            | 10.200.0.10 /24         | VLAN 20 – APP   | Flask application server |

---

### PC3 (DB)
| **Interface** | **IP Address / Prefix** | **VLAN / Zone** | **Purpose / Notes**     |
|---------------|-------------------------|-----------------|-------------------------|
| E0            | 10.30.0.10 /24          | VLAN 30 – DB    | PostgreSQL database     |

---

### CLIENT-PC4
| **Interface** | **IP Address / Prefix** | **VLAN / Zone** | **Purpose / Notes** |
|---------------|-------------------------|-----------------|---------------------|
| E0            | DHCP                    | VLAN 50 – USER  | End-user client     |

---

### CLIENT-PC5
| **Interface** | **IP Address / Prefix** | **VLAN / Zone** | **Purpose / Notes** |
|---------------|-------------------------|-----------------|---------------------|
| E0            | DHCP                    | VLAN 50 – USER  | End-user client     |

