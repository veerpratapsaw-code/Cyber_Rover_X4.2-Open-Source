import React, { useState } from 'react';
import { ChevronUp, ShieldCheck, Cpu, ArrowUpRight, Award, Radio, X, Sparkles, Code, GitBranch } from 'lucide-react';
import { smoothScrollTo } from '../../hooks/useSmoothScroll';

export default function FooterFinale() {
  const [showCreatorModal, setShowCreatorModal] = useState(false);

  const scrollToTop = () => {
    smoothScrollTo('hero');
  };

  return (
    <footer
      id="finale"
      style={{
        background: 'linear-gradient(180deg, var(--bg-base) 0%, #020305 100%)',
        borderTop: '1px solid rgba(0, 217, 255, 0.15)',
        padding: 'clamp(2.5rem, 6vw, 5rem) 0 var(--space-8) 0',
        fontFamily: 'var(--font-body)',
        position: 'relative',
        overflow: 'hidden'
      }}
    >
      {/* High-Tech Background Atmospheric Radial Glows */}
      <div style={{
        position: 'absolute',
        top: '15%',
        left: '50%',
        transform: 'translateX(-50%)',
        width: '90vw',
        height: '35vw',
        background: 'radial-gradient(ellipse at center, rgba(0, 217, 255, 0.09) 0%, rgba(22, 119, 255, 0.03) 50%, transparent 75%)',
        filter: 'blur(70px)',
        pointerEvents: 'none'
      }} />

      <div className="container" style={{ position: 'relative', zIndex: 1 }}>
        {/* ============================================================ */}
        {/* CONCISE MERGED CLIMAX                                        */}
        {/* ============================================================ */}
        <div style={{ textAlign: 'center', maxWidth: '820px', margin: '0 auto clamp(2rem, 5vw, 3.5rem)' }}>
          {/* Exhibition Badge */}
          <div className="reveal-3d" style={{
            display: 'inline-flex',
            alignItems: 'center',
            gap: '8px',
            padding: '4px 14px',
            background: 'rgba(57, 229, 140, 0.08)',
            border: '1px solid rgba(57, 229, 140, 0.3)',
            borderRadius: 'var(--radius-full)',
            marginBottom: 'var(--space-4)'
          }}>
            <span className="animate-blink" style={{ width: '6px', height: '6px', borderRadius: '50%', background: 'var(--status-nominal)', boxShadow: '0 0 8px var(--status-nominal)' }} />
            <span style={{ fontFamily: 'var(--font-mono)', fontSize: '0.6875rem', fontWeight: 700, color: 'var(--status-nominal)', letterSpacing: '0.14em' }}>
              ROBOTICS ENGINEERING EXHIBITION // 2026 PROTOTYPE
            </span>
          </div>

          {/* 3 Bold Action Words (Single-Line Fit) */}
          <div className="reveal-3d" style={{
            display: 'flex',
            justifyContent: 'center',
            alignItems: 'center',
            gap: 'clamp(0.5rem, 2.5vw, 2.5rem)',
            fontFamily: 'var(--font-heading)',
            fontSize: 'clamp(1.5rem, 4vw, 3.25rem)',
            fontWeight: 800,
            letterSpacing: '0.12em',
            color: 'var(--accent-cyan)',
            marginBottom: 'var(--space-4)',
            textShadow: '0 0 35px rgba(0, 217, 255, 0.45)',
            flexWrap: 'nowrap',
            whiteSpace: 'nowrap'
          }}>
            <span>MOVE.</span>
            <span style={{ opacity: 0.35, fontSize: '0.7em' }}>//</span>
            <span>SENSE.</span>
            <span style={{ opacity: 0.35, fontSize: '0.7em' }}>//</span>
            <span>INSPECT.</span>
          </div>

          {/* Concise Mission Manifesto */}
          <p className="reveal-3d" style={{
            fontSize: 'clamp(0.875rem, 1.8vw, 1.0625rem)',
            color: 'var(--text-secondary)',
            lineHeight: 1.65,
            margin: '0 auto var(--space-5)',
            maxWidth: '640px'
          }}>
            Engineering remote reconnaissance and environmental inspection for human safety across hazardous frontiers. Operator-controlled multi-gas indication and spatial proximity assistance before human teams commit to entry.
          </p>

          {/* 3 Unified Spec Badges */}
          <div className="reveal-3d" style={{
            display: 'flex',
            justifyContent: 'center',
            flexWrap: 'wrap',
            gap: '8px',
            marginBottom: 'var(--space-6)'
          }}>
            <span style={{ fontFamily: 'var(--font-mono)', fontSize: '0.6875rem', padding: '5px 12px', background: 'var(--bg-elevated)', border: '1px solid var(--border-subtle)', borderRadius: 'var(--radius-xs)', color: 'var(--text-primary)' }}>
              PLATFORM: <strong style={{ color: 'var(--status-nominal)' }}>MODEL X4.2 (PROTOTYPE)</strong>
            </span>
            <span style={{ fontFamily: 'var(--font-mono)', fontSize: '0.6875rem', padding: '5px 12px', background: 'var(--bg-elevated)', border: '1px solid var(--border-subtle)', borderRadius: 'var(--radius-xs)', color: 'var(--text-primary)' }}>
              SYSTEM: <strong style={{ color: 'var(--accent-cyan)' }}>6-NODE DECOUPLED</strong>
            </span>
            <span style={{ fontFamily: 'var(--font-mono)', fontSize: '0.6875rem', padding: '5px 12px', background: 'var(--bg-elevated)', border: '1px solid var(--border-subtle)', borderRadius: 'var(--radius-xs)', color: 'var(--text-primary)' }}>
              STATUS: <strong style={{ color: 'var(--status-nominal)' }}>DEMONSTRATED PROTOTYPE</strong>
            </span>
          </div>

          {/* Return-to-Top Button */}
          <div className="reveal-3d">
            <button
              onClick={scrollToTop}
              style={{
                padding: '8px 20px',
                background: 'rgba(255, 255, 255, 0.03)',
                border: '1px solid var(--border-medium)',
                borderRadius: 'var(--radius-full)',
                color: 'var(--text-primary)',
                fontFamily: 'var(--font-mono)',
                fontSize: '0.6875rem',
                fontWeight: 600,
                display: 'inline-flex',
                alignItems: 'center',
                gap: '6px',
                cursor: 'pointer',
                transition: 'all 0.25s ease'
              }}
              onMouseEnter={e => { e.currentTarget.style.borderColor = 'var(--accent-cyan)'; e.currentTarget.style.color = 'var(--accent-cyan)'; e.currentTarget.style.boxShadow = '0 0 16px rgba(0, 217, 255, 0.3)'; }}
              onMouseLeave={e => { e.currentTarget.style.borderColor = 'var(--border-medium)'; e.currentTarget.style.color = 'var(--text-primary)'; e.currentTarget.style.boxShadow = 'none'; }}
            >
              <ChevronUp size={13} />
              <span>RETURN TO TOP TELEMETRY</span>
            </button>
          </div>
        </div>

        {/* ============================================================ */}
        {/* MONUMENTAL TYPOGRAPHY (CLEAN FULL-WIDTH, NO VERTICAL CLUTTER) */}
        {/* ============================================================ */}
        <div style={{
          width: '100%',
          maxWidth: '1240px',
          margin: '0 auto clamp(2.5rem, 6vw, 4.5rem)',
          padding: '0 var(--space-4)',
          textAlign: 'center'
        }}>
          <svg
            viewBox="0 0 1100 135"
            style={{
              width: '100%',
              height: 'auto',
              display: 'block',
              overflow: 'visible',
              filter: 'drop-shadow(0 15px 40px rgba(0, 0, 0, 0.95)) drop-shadow(0 0 35px rgba(0, 217, 255, 0.25))'
            }}
          >
            <defs>
              <linearGradient id="chromeGradient" x1="0" y1="0" x2="0" y2="1">
                <stop offset="0%" stopColor="#FFFFFF" />
                <stop offset="45%" stopColor="#E2E8F0" />
                <stop offset="85%" stopColor="#64748B" />
                <stop offset="100%" stopColor="#334155" />
              </linearGradient>
              <linearGradient id="cyanGradient" x1="0" y1="0" x2="0" y2="1">
                <stop offset="0%" stopColor="#E0F2FE" />
                <stop offset="40%" stopColor="#00E5FF" />
                <stop offset="100%" stopColor="#0284C7" />
              </linearGradient>
              <filter id="cyanAura" x="-20%" y="-20%" width="140%" height="140%">
                <feGaussianBlur stdDeviation="8" result="blur" />
                <feComposite in="SourceGraphic" in2="blur" operator="over" />
              </filter>
            </defs>
            <text
              x="50%"
              y="105"
              textAnchor="middle"
              fontFamily="var(--font-heading), 'Outfit', sans-serif"
              fontWeight="900"
              fontSize="122"
              letterSpacing="-0.035em"
            >
              <tspan fill="url(#chromeGradient)">CYBERROVER </tspan>
              <tspan fill="url(#cyanGradient)" filter="url(#cyanAura)">X4</tspan>
            </text>
          </svg>
        </div>
        {/* ============================================================ */}
        {/* OPEN SOURCE HARDWARE & CODE REPOSITORY CARD                   */}
        {/* ============================================================ */}
        <div style={{
          maxWidth: '820px',
          margin: '0 auto clamp(2rem, 5vw, 3.5rem)',
          padding: 'clamp(20px, 3.5vw, 32px)',
          background: 'linear-gradient(145deg, rgba(0, 217, 255, 0.05) 0%, rgba(22, 119, 255, 0.02) 100%)',
          border: '1px solid rgba(0, 217, 255, 0.35)',
          borderRadius: 'var(--radius-sm)',
          textAlign: 'center',
          boxShadow: '0 0 40px rgba(0, 217, 255, 0.08)'
        }}>
          <div style={{
            display: 'inline-flex',
            alignItems: 'center',
            gap: '8px',
            padding: '4px 14px',
            background: 'rgba(0, 217, 255, 0.1)',
            border: '1px solid var(--accent-cyan)',
            borderRadius: 'var(--radius-full)',
            marginBottom: '14px'
          }}>
            <Code size={13} style={{ color: 'var(--accent-cyan)' }} />
            <span style={{ fontFamily: 'var(--font-mono)', fontSize: '0.6875rem', fontWeight: 700, color: 'var(--accent-cyan)', letterSpacing: '0.12em' }}>
              PUBLIC OPEN-SOURCE RELEASE // HARDWARE & SOFTWARE
            </span>
          </div>

          <h3 style={{
            fontFamily: 'var(--font-heading)',
            fontSize: 'clamp(1.25rem, 2.5vw, 1.875rem)',
            fontWeight: 800,
            color: 'var(--text-primary)',
            margin: '0 0 10px 0'
          }}>
            100% OPEN SOURCE &amp; REPRODUCIBLE
          </h3>

          <p style={{
            fontSize: 'clamp(0.8125rem, 1.8vw, 0.9375rem)',
            color: 'var(--text-secondary)',
            lineHeight: 1.65,
            maxWidth: '660px',
            margin: '0 auto 20px auto'
          }}>
            CyberRover X4.2 is fully open source under multi-licensing (Firmware: MIT · Hardware: CERN-OHL-S-2.0 · Docs: CC BY 4.0). Microcontroller firmware for all 5 nodes, text wiring guides, BOM, cost breakdowns, and ground station code are available in the public repository.
          </p>

          <div style={{ display: 'flex', justifyContent: 'center', gap: '12px', flexWrap: 'wrap' }}>
            <a
              href="https://github.com/veerpratapsaw/cyberrover-x4"
              target="_blank"
              rel="noopener noreferrer"
              style={{
                display: 'inline-flex',
                alignItems: 'center',
                gap: '8px',
                padding: '12px 26px',
                background: 'var(--accent-cyan)',
                border: 'none',
                borderRadius: 'var(--radius-xs)',
                color: 'var(--text-inverse)',
                fontFamily: 'var(--font-mono)',
                fontSize: '0.75rem',
                fontWeight: 700,
                letterSpacing: '0.08em',
                textDecoration: 'none',
                boxShadow: '0 0 24px rgba(0, 217, 255, 0.45)',
                transition: 'all 0.2s ease'
              }}
              onMouseEnter={e => {
                e.currentTarget.style.boxShadow = '0 0 35px rgba(0, 217, 255, 0.7)';
              }}
              onMouseLeave={e => {
                e.currentTarget.style.boxShadow = '0 0 24px rgba(0, 217, 255, 0.45)';
              }}
            >
              <GitBranch size={16} />
              <span>ACCESS REPOSITORY ON GITHUB</span>
              <ArrowUpRight size={15} />
            </a>
          </div>
        </div>

        {/* ============================================================ */}
        {/* BOTTOM ATTRIBUTION & COPYRIGHT STRIP                          */}
        {/* ============================================================ */}
        <div style={{
          borderTop: '1px solid rgba(255, 255, 255, 0.08)',
          paddingTop: 'var(--space-6)',
          display: 'flex',
          justifyContent: 'space-between',
          alignItems: 'center',
          flexWrap: 'wrap',
          gap: '16px'
        }}>
          {/* Creator Attribution (Clickable for Dossier) */}
          <div
            onClick={() => setShowCreatorModal(true)}
            style={{
              display: 'flex',
              alignItems: 'center',
              gap: '10px',
              cursor: 'pointer',
              padding: '6px 14px',
              background: 'rgba(0, 217, 255, 0.05)',
              border: '1px solid rgba(0, 217, 255, 0.25)',
              borderRadius: 'var(--radius-xs)',
              transition: 'all 0.25s ease'
            }}
            onMouseEnter={e => {
              e.currentTarget.style.borderColor = 'var(--accent-cyan)';
              e.currentTarget.style.background = 'rgba(0, 217, 255, 0.12)';
              e.currentTarget.style.boxShadow = '0 0 16px rgba(0, 217, 255, 0.25)';
            }}
            onMouseLeave={e => {
              e.currentTarget.style.borderColor = 'rgba(0, 217, 255, 0.25)';
              e.currentTarget.style.background = 'rgba(0, 217, 255, 0.05)';
              e.currentTarget.style.boxShadow = 'none';
            }}
          >
            <span className="animate-blink" style={{ width: '8px', height: '8px', borderRadius: '50%', background: 'var(--accent-cyan)', boxShadow: '0 0 10px var(--accent-cyan)' }} />
            <div style={{
              fontFamily: 'var(--font-heading)',
              fontSize: 'clamp(0.9375rem, 2vw, 1.125rem)',
              fontWeight: 800,
              color: 'var(--text-primary)',
              letterSpacing: '0.04em'
            }}>
              VEER PRATAP SAW
            </div>
            <span style={{
              fontFamily: 'var(--font-mono)',
              fontSize: '0.625rem',
              color: 'var(--accent-cyan)',
              letterSpacing: '0.08em'
            }}>
              // PROJECT CREATOR & LEAD ARCHITECT
            </span>
          </div>

          {/* Minimal Status & Year */}
        {/* Verbatim Final Engineering & Regulatory Disclaimer */}
        <div style={{
          padding: '12px 18px',
          background: 'rgba(255, 176, 32, 0.05)',
          border: '1px solid rgba(255, 176, 32, 0.25)',
          borderRadius: 'var(--radius-xs)',
          marginBottom: 'var(--space-6)',
          fontFamily: 'var(--font-mono)',
          fontSize: '0.6875rem',
          color: 'var(--text-secondary)',
          lineHeight: 1.6,
          textAlign: 'center'
        }}>
          <strong style={{ color: 'var(--status-warning)' }}>ENGINEERING & REGULATORY DISCLAIMER:</strong> CyberRover X4.2 is a student-built engineering prototype for remote reconnaissance and environmental inspection. It is not currently certified for explosion-proof, intrinsically safe, mining, fire-entry, or military deployment. Future X5 specifications represent proposed engineering development.
        </div>

        {/* Bottom Metadata */}
        <div style={{
          display: 'flex',
          justifyContent: 'space-between',
          alignItems: 'center',
          flexWrap: 'wrap',
          gap: '16px'
        }}>
          <div style={{
            fontFamily: 'var(--font-mono)',
            fontSize: '0.75rem',
            color: 'var(--text-muted)',
            display: 'flex',
            gap: '14px',
            alignItems: 'center',
            flexWrap: 'wrap'
          }}>
            <span>© 2026 CYBERROVER X4.2</span>
            <span>·</span>
            <span>RBOTICS LABS</span>
            <span>·</span>
            <span style={{ color: 'var(--status-nominal)' }}>OPERATOR-CONTROLLED PROTOTYPE</span>
            <span>·</span>
            <span>ALL RIGHTS RESERVED</span>
          </div>
        </div>
      </div>
    </div>

      {/* ============================================================ */}
      {/* INTERACTIVE CREATOR DOSSIER MODAL                            */}
      {/* ============================================================ */}
      {showCreatorModal && (
        <div style={{
          position: 'fixed',
          inset: 0,
          background: 'rgba(3, 5, 8, 0.88)',
          backdropFilter: 'blur(16px)',
          zIndex: 9999,
          display: 'flex',
          alignItems: 'center',
          justifyContent: 'center',
          padding: '20px'
        }}>
          <div style={{
            background: 'linear-gradient(145deg, rgba(16, 20, 26, 0.98), rgba(7, 9, 12, 0.99))',
            border: '1px solid var(--accent-cyan)',
            borderRadius: 'var(--radius-md)',
            padding: 'clamp(20px, 4vw, 36px)',
            maxWidth: '560px',
            width: '100%',
            position: 'relative',
            boxShadow: '0 20px 60px rgba(0, 0, 0, 0.85), 0 0 35px rgba(0, 217, 255, 0.3)'
          }}>
            {/* Close Button */}
            <button
              onClick={() => setShowCreatorModal(false)}
              aria-label="Close Dossier"
              style={{
                position: 'absolute',
                top: '16px',
                right: '16px',
                background: 'rgba(255, 255, 255, 0.06)',
                border: '1px solid var(--border-subtle)',
                borderRadius: 'var(--radius-xs)',
                color: 'var(--text-primary)',
                width: '32px',
                height: '32px',
                display: 'flex',
                alignItems: 'center',
                justifyContent: 'center',
                cursor: 'pointer'
              }}
            >
              <X size={16} />
            </button>

            {/* Modal Header */}
            <div style={{ display: 'flex', alignItems: 'center', gap: '10px', marginBottom: '14px' }}>
              <Sparkles size={20} style={{ color: 'var(--accent-cyan)' }} />
              <span style={{ fontFamily: 'var(--font-mono)', fontSize: '0.75rem', color: 'var(--accent-cyan)', letterSpacing: '0.14em' }}>
                // ARCHITECT & CREATOR DOSSIER
              </span>
            </div>

            <h3 style={{ fontFamily: 'var(--font-heading)', fontSize: '1.75rem', fontWeight: 800, color: 'var(--text-primary)', margin: '0 0 6px 0' }}>
              VEER PRATAP SAW
            </h3>

            <div style={{ fontFamily: 'var(--font-mono)', fontSize: '0.8125rem', color: 'var(--status-nominal)', marginBottom: '16px' }}>
              PROJECT CREATOR // LEAD EMBEDDED & ROBOTICS ARCHITECT
            </div>

            <p style={{ fontSize: '0.9375rem', color: 'var(--text-secondary)', lineHeight: 1.6, marginBottom: '20px' }}>
              Designed, built, and programmed the complete <strong>CyberRover Model X4</strong> multi-node robotics continuum and conceived the next-generation <strong>CyberRover X5</strong> deep-mine reconnaissance platform.
            </p>

            <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: '10px', marginBottom: '20px', fontFamily: 'var(--font-mono)', fontSize: '0.75rem' }}>
              <div style={{ padding: '10px', background: 'rgba(255,255,255,0.03)', borderRadius: 'var(--radius-xs)', border: '1px solid var(--border-subtle)' }}>
                <div style={{ color: 'var(--text-muted)', fontSize: '0.625rem' }}>RESEARCH LAB</div>
                <div style={{ color: 'var(--text-primary)', fontWeight: 600 }}>RBOTICS | Hazaribagh</div>
              </div>
              <div style={{ padding: '10px', background: 'rgba(255,255,255,0.03)', borderRadius: 'var(--radius-xs)', border: '1px solid var(--border-subtle)' }}>
                <div style={{ color: 'var(--text-muted)', fontSize: '0.625rem' }}>HARDWARE PROTOTYPE</div>
                <div style={{ color: 'var(--accent-cyan)', fontWeight: 600 }}>CyberRover X4.2 (Active)</div>
              </div>
              <div style={{ padding: '10px', background: 'rgba(255,255,255,0.03)', borderRadius: 'var(--radius-xs)', border: '1px solid var(--border-subtle)' }}>
                <div style={{ color: 'var(--text-muted)', fontSize: '0.625rem' }}>FUTURE ROADMAP</div>
                <div style={{ color: 'var(--accent-cyan)', fontWeight: 600 }}>CyberRover X5 Deep Recon</div>
              </div>
              <div style={{ padding: '10px', background: 'rgba(255,255,255,0.03)', borderRadius: 'var(--radius-xs)', border: '1px solid var(--border-subtle)' }}>
                <div style={{ color: 'var(--text-muted)', fontSize: '0.625rem' }}>ARCHITECTURE</div>
                <div style={{ color: 'var(--status-nominal)', fontWeight: 600 }}>6-Node Dual-Bus Topology</div>
              </div>
            </div>

            <button
              onClick={() => setShowCreatorModal(false)}
              style={{
                width: '100%',
                padding: '12px',
                background: 'var(--accent-cyan)',
                border: 'none',
                borderRadius: 'var(--radius-xs)',
                color: 'var(--text-inverse)',
                fontFamily: 'var(--font-mono)',
                fontSize: '0.8125rem',
                fontWeight: 700,
                cursor: 'pointer'
              }}
            >
              CLOSE DOSSIER
            </button>
          </div>
        </div>
      )}
    </footer>
  );
}
