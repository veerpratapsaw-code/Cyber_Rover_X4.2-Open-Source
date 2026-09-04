import React, { useState } from 'react';
import { Laptop, Cpu, Wifi, Radio, Camera, Disc, Eye, Activity, ShieldCheck, ShieldAlert, Zap, AlertTriangle } from 'lucide-react';

const NODES = [
  {
    id: 'node01',
    layer: 'layer1',
    num: 'NODE 01',
    name: 'Remote Controller',
    mcu: 'ESP32 DevKit V1 (240MHz)',
    bus: 'ESP-NOW 2.4GHz RF (Dedicated)',
    color: '#00e5ff',
    desc: 'FreeRTOS Dual-Core architecture. Core 0 executes 0.96" SSD1306 OLED display UI (Cyber OS); Core 1 handles analog joystick sampling, calibration and peer-to-peer radio transmission.',
    specs: ['0.96" SSD1306 I2C OLED', 'Peer-to-Peer ESP-NOW RF', '18650 Li-Ion Cell Power']
  },
  {
    id: 'node02',
    layer: 'layer1',
    num: 'NODE 02',
    name: 'Rover Master Gateway',
    mcu: 'ESP32-S3 DevKit (240MHz)',
    bus: 'ESP-NOW RX + Hardware UART TX',
    color: '#39e58c',
    desc: 'Receives binary packet frames from the remote controller. Verifies CRC-8 checksums, drives WS2812 RGB state lights, enforces 500ms safety watchdog, and bridges commands to Uno via UART at 38400 baud.',
    specs: ['CRC-8 Packet Verification', 'WS2812 State LED', '500ms Emergency Failsafe']
  },
  {
    id: 'node03',
    layer: 'layer1',
    num: 'NODE 03',
    name: 'Motor & Radar Brain',
    mcu: 'Arduino Uno (ATmega328P 16MHz)',
    bus: 'UART RX + BTS7960 Drivers',
    color: '#00e5ff',
    desc: 'Hardware motor controller. Drives dual BTS7960 high-current MOSFET bridges with PWM acceleration ramping, samples 3x HC-SR04 ultrasonic obstacle array, and generates tactical siren audio alerts.',
    specs: ['Dual BTS7960 High-Current Drivers', 'PWM Acceleration Ramping', '10-Tone Non-Blocking Sound Engine']
  },
  {
    id: 'node04',
    layer: 'layer2',
    num: 'NODE 04',
    name: 'Gas Sensor Node',
    mcu: 'Arduino Nano (ATmega328P 16MHz)',
    bus: 'Analog ADC + I2C LCD + UART',
    color: '#ff9500',
    desc: 'Dedicated hazardous gas acquisition module. Continuously reads MQ-4 Methane, MQ-7 Carbon Monoxide, and MQ-135 Air Quality sensors, displaying local raw ADC values on a 16x2 I2C LCD before relaying.',
    specs: ['MQ-4 Methane Indication', 'MQ-7 Carbon Monoxide Indication', '16x2 I2C Local LCD Indication']
  },
  {
    id: 'node05',
    layer: 'layer2',
    num: 'NODE 05',
    name: 'Telemetry Hub & Gateway',
    mcu: 'ESP32-CAM (Sensor Gateway)',
    bus: 'Wi-Fi 802.11 b/g/n + I2C BMP280',
    color: '#ff4444',
    desc: 'Serves as environmental telemetry gateway and hub. Samples BMP280 barometric pressure/relative elevation and DHT11 climate readings, packaging sensor readings into JSON packets for the Wi-Fi telemetry stream.',
    specs: ['Wi-Fi Telemetry Server', 'BMP280 Barometer & Relative Altitude', 'JSON Telemetry REST Gateway']
  },
  {
    id: 'node06',
    layer: 'layer2',
    num: 'NODE 06',
    name: 'Ground Command Cockpit',
    mcu: 'Laptop Ground Station (Host)',
    bus: 'Wi-Fi WebSockets / REST / Web Audio',
    color: '#1677ff',
    desc: 'Mission command software. Renders live smartphone camera FPV optical feed, real-time gas indication graphs, synthetic voice alerts, battery voltage telemetry, and manual override controls outside the inspection area.',
    specs: ['Web Audio Synthesizer', 'Real-Time Telemetry Graphs', 'Custom High-Visibility HUD Reticle']
  }
];

export default function SystemTopologyDiagram() {
  const [activeLayer, setActiveLayer] = useState('all'); // 'all', 'layer1', 'layer2'
  const [wifiBlackout, setWifiBlackout] = useState(false);

  return (
    <div className="tech-card reticle-box" style={{
      background: 'linear-gradient(145deg, rgba(16, 20, 26, 0.95), rgba(7, 9, 12, 0.98))',
      padding: 'clamp(16px, 3vw, 28px)',
      borderRadius: '24px',
      border: '1px solid rgba(0, 217, 255, 0.25)'
    }}>
      {/* Header & Controls */}
      <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '24px', flexWrap: 'wrap', gap: '14px' }}>
        <div>
          <div style={{ display: 'flex', alignItems: 'center', gap: '8px' }}>
            <span style={{ display: 'inline-block', width: '8px', height: '8px', borderRadius: '50%', background: '#00e5ff', boxShadow: '0 0 10px #00e5ff' }} />
            <span style={{ fontFamily: 'var(--font-mono)', fontSize: '0.75rem', color: 'var(--accent-cyan)', letterSpacing: '0.1em' }}>
              6-NODE HETEROGENEOUS TOPOLOGY // DUAL-LAYER DECOUPLING
            </span>
          </div>
          <h3 style={{ fontFamily: 'var(--font-heading)', fontSize: '1.35rem', fontWeight: 700, margin: '4px 0 0 0', color: 'var(--text-primary)' }}>
            Physical Node Hierarchy & Protocol Dataflow
          </h3>
        </div>

        {/* Filter Buttons & Blackout Simulator */}
        <div style={{ display: 'flex', gap: '10px', flexWrap: 'wrap', alignItems: 'center' }}>
          {/* Layer Filters */}
          <div style={{ display: 'flex', gap: '4px', background: 'rgba(255, 255, 255, 0.05)', padding: '4px', borderRadius: '8px', border: '1px solid rgba(255, 255, 255, 0.1)' }}>
            {[
              { id: 'all', label: 'ALL 6 NODES' },
              { id: 'layer1', label: 'LAYER 1: DRIVE (ESP-NOW)' },
              { id: 'layer2', label: 'LAYER 2: TELEMETRY (WI-FI)' }
            ].map(tab => (
              <button
                key={tab.id}
                onClick={() => setActiveLayer(tab.id)}
                style={{
                  padding: '6px 12px',
                  fontSize: '0.6875rem',
                  fontFamily: 'var(--font-mono)',
                  border: 'none',
                  borderRadius: '6px',
                  cursor: 'pointer',
                  background: activeLayer === tab.id ? 'var(--accent-cyan)' : 'transparent',
                  color: activeLayer === tab.id ? '#07090c' : 'rgba(255,255,255,0.7)',
                  fontWeight: 700
                }}
              >
                {tab.label}
              </button>
            ))}
          </div>

          {/* Wi-Fi Blackout Simulation Toggle */}
          <button
            onClick={() => setWifiBlackout(!wifiBlackout)}
            style={{
              padding: '6px 14px',
              fontSize: '0.6875rem',
              fontFamily: 'var(--font-mono)',
              borderRadius: '8px',
              cursor: 'pointer',
              fontWeight: 700,
              display: 'flex',
              alignItems: 'center',
              gap: '6px',
              background: wifiBlackout ? '#ff3b30' : 'rgba(255, 68, 68, 0.15)',
              border: `1px solid ${wifiBlackout ? '#ff3b30' : 'rgba(255, 68, 68, 0.4)'}`,
              color: wifiBlackout ? '#fff' : '#ff4444',
              transition: 'all 0.2s ease'
            }}
          >
            <AlertTriangle size={14} />
            <span>{wifiBlackout ? 'SIMULATING WI-FI COLLAPSE [ACTIVE]' : 'SIMULATE WI-FI BLACKOUT'}</span>
          </button>
        </div>
      </div>

      {/* Blackout Banner Alert */}
      {wifiBlackout && (
        <div style={{
          background: 'rgba(255, 59, 48, 0.15)',
          border: '1px solid #ff3b30',
          borderRadius: '12px',
          padding: '12px 16px',
          marginBottom: '20px',
          display: 'flex',
          alignItems: 'center',
          gap: '12px'
        }}>
          <ShieldAlert size={20} style={{ color: '#ff3b30', flexShrink: 0 }} />
          <div style={{ fontSize: '0.8125rem', color: '#fff', lineHeight: 1.4 }}>
            <strong>DISASTER BLACKOUT DEMONSTRATION ACTIVE:</strong> In rubble or thick reinforced concrete, Wi-Fi Layer 2 has dropped (Video/Telemetry offline). 
            <span style={{ color: '#39e58c', fontWeight: 'bold' }}> However, Layer 1 (ESP-NOW Drive Core) remains 100% OPERATIONAL with &lt;10ms latency</span>, enabling emergency vehicle extraction!
          </div>
        </div>
      )}

      {/* Two Architecture Layers Container */}
      <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fit, minmax(min(100%, 420px), 1fr))', gap: '20px' }}>
        
        {/* ========================================================= */}
        {/* LAYER 1: DRIVE CORE (100% OFFLINE)                       */}
        {/* ========================================================= */}
        {(activeLayer === 'all' || activeLayer === 'layer1') && (
          <div style={{
            background: 'rgba(0, 217, 255, 0.03)',
            border: '1px solid rgba(0, 217, 255, 0.25)',
            borderRadius: '16px',
            padding: '20px'
          }}>
            {/* Layer Title */}
            <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '16px', borderBottom: '1px solid rgba(0, 217, 255, 0.15)', paddingBottom: '10px' }}>
              <div style={{ display: 'flex', alignItems: 'center', gap: '8px' }}>
                <Radio size={18} style={{ color: '#00e5ff' }} />
                <span style={{ fontFamily: 'var(--font-heading)', fontSize: '1rem', fontWeight: 700, color: '#fff' }}>
                  LAYER 1: REAL-TIME DRIVE CORE
                </span>
              </div>
              <span style={{
                fontFamily: 'var(--font-mono)',
                fontSize: '0.625rem',
                background: 'rgba(57, 229, 140, 0.15)',
                color: '#39e58c',
                padding: '2px 8px',
                borderRadius: '4px',
                border: '1px solid #39e58c'
              }}>
                100% OFFLINE (ZERO WI-FI)
              </span>
            </div>

            {/* Nodes 01, 02, 03 */}
            <div style={{ display: 'flex', flexDirection: 'column', gap: '12px' }}>
              {NODES.filter(n => n.layer === 'layer1').map(node => (
                <div
                  key={node.id}
                  style={{
                    background: 'rgba(255, 255, 255, 0.03)',
                    border: `1px solid ${node.color}40`,
                    borderRadius: '12px',
                    padding: '14px',
                    transition: 'all 0.25s ease'
                  }}
                >
                  <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '6px' }}>
                    <div style={{ display: 'flex', alignItems: 'center', gap: '8px' }}>
                      <span style={{ fontFamily: 'var(--font-mono)', fontSize: '0.6875rem', color: node.color, fontWeight: 700 }}>
                        {node.num}
                      </span>
                      <span style={{ fontFamily: 'var(--font-heading)', fontSize: '0.9375rem', fontWeight: 700, color: '#fff' }}>
                        {node.name}
                      </span>
                    </div>
                    <span style={{ fontFamily: 'var(--font-mono)', fontSize: '0.625rem', color: 'rgba(255,255,255,0.6)' }}>
                      {node.mcu}
                    </span>
                  </div>
                  <div style={{ fontFamily: 'var(--font-mono)', fontSize: '0.6875rem', color: node.color, marginBottom: '6px' }}>
                    BUS: {node.bus}
                  </div>
                  <p style={{ fontSize: '0.75rem', color: 'rgba(255, 255, 255, 0.7)', margin: '0 0 10px 0', lineHeight: 1.4 }}>
                    {node.desc}
                  </p>
                  <div style={{ display: 'flex', flexWrap: 'wrap', gap: '6px' }}>
                    {node.specs.map((s, idx) => (
                      <span key={idx} style={{
                        fontFamily: 'var(--font-mono)',
                        fontSize: '0.625rem',
                        background: 'rgba(255, 255, 255, 0.05)',
                        color: 'rgba(255, 255, 255, 0.8)',
                        padding: '2px 6px',
                        borderRadius: '4px'
                      }}>
                        ✓ {s}
                      </span>
                    ))}
                  </div>
                </div>
              ))}
            </div>
          </div>
        )}

        {/* ========================================================= */}
        {/* LAYER 2: TELEMETRY & OPTICAL CORE (WI-FI)                */}
        {/* ========================================================= */}
        {(activeLayer === 'all' || activeLayer === 'layer2') && (
          <div style={{
            background: wifiBlackout ? 'rgba(255, 59, 48, 0.04)' : 'rgba(22, 119, 255, 0.03)',
            border: `1px solid ${wifiBlackout ? 'rgba(255, 59, 48, 0.4)' : 'rgba(22, 119, 255, 0.25)'}`,
            borderRadius: '16px',
            padding: '20px',
            opacity: wifiBlackout ? 0.6 : 1,
            transition: 'all 0.3s ease'
          }}>
            {/* Layer Title */}
            <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '16px', borderBottom: '1px solid rgba(22, 119, 255, 0.15)', paddingBottom: '10px' }}>
              <div style={{ display: 'flex', alignItems: 'center', gap: '8px' }}>
                <Wifi size={18} style={{ color: wifiBlackout ? '#ff4444' : '#1677ff' }} />
                <span style={{ fontFamily: 'var(--font-heading)', fontSize: '1rem', fontWeight: 700, color: '#fff' }}>
                  LAYER 2: TELEMETRY & OPTICAL CORE
                </span>
              </div>
              <span style={{
                fontFamily: 'var(--font-mono)',
                fontSize: '0.625rem',
                background: wifiBlackout ? 'rgba(255, 59, 48, 0.2)' : 'rgba(22, 119, 255, 0.15)',
                color: wifiBlackout ? '#ff4444' : '#1677ff',
                padding: '2px 8px',
                borderRadius: '4px',
                border: `1px solid ${wifiBlackout ? '#ff4444' : '#1677ff'}`
              }}>
                {wifiBlackout ? 'WI-FI SIGNAL LOST' : 'WI-FI 2.4GHz REST + MJPEG'}
              </span>
            </div>

            {/* Nodes 04, 05, 06 */}
            <div style={{ display: 'flex', flexDirection: 'column', gap: '12px' }}>
              {NODES.filter(n => n.layer === 'layer2').map(node => (
                <div
                  key={node.id}
                  style={{
                    background: 'rgba(255, 255, 255, 0.03)',
                    border: `1px solid ${wifiBlackout ? '#ff444440' : `${node.color}40`}`,
                    borderRadius: '12px',
                    padding: '14px',
                    transition: 'all 0.25s ease'
                  }}
                >
                  <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '6px' }}>
                    <div style={{ display: 'flex', alignItems: 'center', gap: '8px' }}>
                      <span style={{ fontFamily: 'var(--font-mono)', fontSize: '0.6875rem', color: wifiBlackout ? '#ff4444' : node.color, fontWeight: 700 }}>
                        {node.num}
                      </span>
                      <span style={{ fontFamily: 'var(--font-heading)', fontSize: '0.9375rem', fontWeight: 700, color: '#fff' }}>
                        {node.name}
                      </span>
                    </div>
                    <span style={{ fontFamily: 'var(--font-mono)', fontSize: '0.625rem', color: 'rgba(255,255,255,0.6)' }}>
                      {node.mcu}
                    </span>
                  </div>
                  <div style={{ fontFamily: 'var(--font-mono)', fontSize: '0.6875rem', color: wifiBlackout ? '#ff4444' : node.color, marginBottom: '6px' }}>
                    BUS: {node.bus}
                  </div>
                  <p style={{ fontSize: '0.75rem', color: 'rgba(255, 255, 255, 0.7)', margin: '0 0 10px 0', lineHeight: 1.4 }}>
                    {node.desc}
                  </p>
                  <div style={{ display: 'flex', flexWrap: 'wrap', gap: '6px' }}>
                    {node.specs.map((s, idx) => (
                      <span key={idx} style={{
                        fontFamily: 'var(--font-mono)',
                        fontSize: '0.625rem',
                        background: 'rgba(255, 255, 255, 0.05)',
                        color: 'rgba(255, 255, 255, 0.8)',
                        padding: '2px 6px',
                        borderRadius: '4px'
                      }}>
                        ✓ {s}
                      </span>
                    ))}
                  </div>
                </div>
              ))}
            </div>
          </div>
        )}
      </div>
    </div>
  );
}
