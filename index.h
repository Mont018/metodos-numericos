<!DOCTYPE html>
<html lang="es">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Métodos Numéricos</title>
<link href="https://fonts.googleapis.com/css2?family=Space+Mono:wght@400;700&family=DM+Sans:wght@300;400;500;600&display=swap" rel="stylesheet">
<style>
  :root {
    --bg: #0a0e1a;
    --bg2: #111827;
    --bg3: #1a2235;
    --accent: #00d4ff;
    --accent2: #7c3aed;
    --accent3: #10b981;
    --accent4: #f59e0b;
    --accent5: #ef4444;
    --accent6: #ec4899;
    --text: #e2e8f0;
    --text2: #94a3b8;
    --text3: #64748b;
    --mono: 'Space Mono', monospace;
    --sans: 'DM Sans', sans-serif;
    --radius: 12px;
    --radius-sm: 8px;
  }

  * { box-sizing: border-box; margin: 0; padding: 0; }

  body {
    background: var(--bg);
    color: var(--text);
    font-family: var(--sans);
    min-height: 100vh;
    overflow-x: hidden;
  }

  /* GRID BG */
  body::before {
    content: '';
    position: fixed;
    inset: 0;
    background-image:
      linear-gradient(rgba(0,212,255,0.03) 1px, transparent 1px),
      linear-gradient(90deg, rgba(0,212,255,0.03) 1px, transparent 1px);
    background-size: 40px 40px;
    pointer-events: none;
    z-index: 0;
  }

  /* ====== HEADER ====== */
  .site-header {
    position: relative;
    z-index: 10;
    padding: 3rem 2rem 2rem;
    text-align: center;
    border-bottom: 1px solid rgba(0,212,255,0.1);
    background: linear-gradient(180deg, rgba(0,212,255,0.05) 0%, transparent 100%);
  }

  .site-header .tag {
    display: inline-block;
    font-family: var(--mono);
    font-size: 11px;
    letter-spacing: 0.2em;
    text-transform: uppercase;
    color: var(--accent);
    border: 1px solid rgba(0,212,255,0.3);
    padding: 4px 14px;
    border-radius: 999px;
    margin-bottom: 1rem;
  }

  .site-header h1 {
    font-family: var(--mono);
    font-size: clamp(1.8rem, 5vw, 3.5rem);
    font-weight: 700;
    color: #fff;
    letter-spacing: -0.02em;
    line-height: 1.1;
  }

  .site-header h1 span {
    color: var(--accent);
    text-shadow: 0 0 40px rgba(0,212,255,0.4);
  }

  .site-header p {
    margin-top: 0.75rem;
    color: var(--text2);
    font-size: 15px;
    max-width: 500px;
    margin-left: auto;
    margin-right: auto;
  }

  .header-stats {
    display: flex;
    justify-content: center;
    gap: 2rem;
    margin-top: 2rem;
    flex-wrap: wrap;
  }

  .stat {
    text-align: center;
  }

  .stat-n {
    font-family: var(--mono);
    font-size: 24px;
    font-weight: 700;
    color: var(--accent);
  }

  .stat-l {
    font-size: 12px;
    color: var(--text3);
    letter-spacing: 0.05em;
  }

  /* ====== NAV ====== */
  .nav-wrap {
    position: sticky;
    top: 0;
    z-index: 100;
    background: rgba(10,14,26,0.92);
    backdrop-filter: blur(16px);
    border-bottom: 1px solid rgba(255,255,255,0.06);
    padding: 0 1.5rem;
    overflow-x: auto;
    scrollbar-width: none;
  }

  .nav-wrap::-webkit-scrollbar { display: none; }

  .nav-inner {
    display: flex;
    gap: 0;
    min-width: max-content;
  }

  .nav-btn {
    font-family: var(--mono);
    font-size: 11px;
    letter-spacing: 0.05em;
    padding: 1rem 1.25rem;
    border: none;
    background: none;
    color: var(--text3);
    cursor: pointer;
    border-bottom: 2px solid transparent;
    transition: all 0.2s;
    white-space: nowrap;
  }

  .nav-btn:hover { color: var(--text); }

  .nav-btn.active {
    color: #fff;
    border-bottom-color: var(--accent);
  }

  /* ====== MAIN ====== */
  .main {
    position: relative;
    z-index: 1;
    max-width: 1100px;
    margin: 0 auto;
    padding: 2rem 1.5rem 4rem;
  }

  /* ====== UNIT OVERVIEW ====== */
  #overview-view { display: block; }
  .unit-grid {
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
    gap: 1.25rem;
    margin-top: 1.5rem;
  }

  .unit-card {
    background: var(--bg2);
    border: 1px solid rgba(255,255,255,0.06);
    border-radius: var(--radius);
    padding: 1.5rem;
    cursor: pointer;
    transition: all 0.2s;
    position: relative;
    overflow: hidden;
  }

  .unit-card::before {
    content: '';
    position: absolute;
    top: 0; left: 0; right: 0;
    height: 2px;
    background: var(--c);
    opacity: 0.8;
  }

  .unit-card:hover {
    border-color: rgba(255,255,255,0.15);
    transform: translateY(-2px);
    background: var(--bg3);
  }

  .unit-num {
    font-family: var(--mono);
    font-size: 11px;
    color: var(--c);
    letter-spacing: 0.1em;
    margin-bottom: 0.5rem;
  }

  .unit-title {
    font-size: 15px;
    font-weight: 600;
    color: #fff;
    margin-bottom: 0.75rem;
    line-height: 1.4;
  }

  .unit-subtemas-preview {
    display: flex;
    flex-direction: column;
    gap: 4px;
    margin-bottom: 1rem;
  }

  .preview-item {
    font-size: 12px;
    color: var(--text3);
    display: flex;
    align-items: center;
    gap: 6px;
  }

  .preview-item::before {
    content: '';
    width: 4px; height: 4px;
    border-radius: 50%;
    background: var(--c);
    flex-shrink: 0;
    opacity: 0.6;
  }

  .unit-footer {
    display: flex;
    align-items: center;
    justify-content: space-between;
    margin-top: 1rem;
    padding-top: 1rem;
    border-top: 1px solid rgba(255,255,255,0.05);
  }

  .badge {
    font-family: var(--mono);
    font-size: 10px;
    padding: 3px 10px;
    border-radius: 999px;
    border: 1px solid;
  }

  .open-arrow {
    font-size: 18px;
    color: var(--text3);
    transition: transform 0.2s;
  }

  .unit-card:hover .open-arrow { transform: translateX(4px); color: var(--c); }

  /* ====== UNIT DETAIL ====== */
  .unit-detail { display: none; }
  .unit-detail.active { display: block; }

  .detail-header {
    display: flex;
    align-items: center;
    gap: 1rem;
    margin-bottom: 1.5rem;
    padding-bottom: 1.5rem;
    border-bottom: 1px solid rgba(255,255,255,0.06);
  }

  .back-btn {
    font-family: var(--mono);
    font-size: 12px;
    padding: 8px 16px;
    border-radius: 999px;
    border: 1px solid rgba(255,255,255,0.1);
    background: transparent;
    color: var(--text2);
    cursor: pointer;
    transition: all 0.2s;
  }

  .back-btn:hover { background: rgba(255,255,255,0.05); color: #fff; }

  .detail-title-wrap h2 {
    font-family: var(--mono);
    font-size: 20px;
    color: #fff;
  }

  .detail-title-wrap p {
    font-size: 13px;
    color: var(--text3);
    margin-top: 2px;
  }

  .subtemas-list {
    display: flex;
    flex-direction: column;
    gap: 1rem;
  }

  /* ====== SUBTEMA ACCORDION ====== */
  .subtema-block {
    background: var(--bg2);
    border: 1px solid rgba(255,255,255,0.06);
    border-radius: var(--radius);
    overflow: hidden;
    transition: border-color 0.2s;
  }

  .subtema-block:hover { border-color: rgba(255,255,255,0.1); }

  .subtema-header {
    display: flex;
    align-items: center;
    gap: 1rem;
    padding: 1.1rem 1.25rem;
    cursor: pointer;
    user-select: none;
  }

  .subtema-num {
    font-family: var(--mono);
    font-size: 11px;
    min-width: 32px;
    color: var(--c);
    font-weight: 700;
  }

  .subtema-name {
    flex: 1;
    font-size: 14px;
    font-weight: 500;
    color: var(--text);
  }

  .has-prog {
    font-family: var(--mono);
    font-size: 10px;
    padding: 3px 10px;
    border-radius: 999px;
    border: 1px solid rgba(16,185,129,0.3);
    color: var(--accent3);
    background: rgba(16,185,129,0.07);
  }

  .chevron {
    font-size: 14px;
    color: var(--text3);
    transition: transform 0.25s;
  }

  .subtema-block.open .chevron { transform: rotate(180deg); }

  .subtema-body {
    display: none;
    padding: 0 1.25rem 1.25rem;
    border-top: 1px solid rgba(255,255,255,0.05);
  }

  .subtema-block.open .subtema-body { display: block; }

  .subtema-body .teoria {
    font-size: 14px;
    color: var(--text2);
    line-height: 1.8;
    margin-bottom: 1.25rem;
    margin-top: 1rem;
  }

  /* ====== PROGRAM WIDGET ====== */
  .prog-widget {
    background: var(--bg);
    border: 1px solid rgba(0,212,255,0.15);
    border-radius: var(--radius-sm);
    overflow: hidden;
  }

  .prog-top-bar {
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 0.6rem 1rem;
    background: rgba(0,212,255,0.04);
    border-bottom: 1px solid rgba(0,212,255,0.1);
  }

  .prog-label {
    font-family: var(--mono);
    font-size: 11px;
    color: var(--accent);
    letter-spacing: 0.05em;
  }

  .dots { display: flex; gap: 5px; }
  .dot { width: 10px; height: 10px; border-radius: 50%; }

  .code-area {
    font-family: var(--mono);
    font-size: 12px;
    line-height: 1.8;
    padding: 1rem;
    color: #a5f3fc;
    background: transparent;
    white-space: pre;
    overflow-x: auto;
  }

  .code-area .kw { color: #c084fc; }
  .code-area .fn { color: #6ee7b7; }
  .code-area .st { color: #fde68a; }
  .code-area .cm { color: #475569; }
  .code-area .nm { color: #fb923c; }

  .prog-inputs {
    padding: 0.75rem 1rem;
    display: flex;
    flex-wrap: wrap;
    gap: 0.75rem;
    border-top: 1px solid rgba(255,255,255,0.05);
    background: rgba(255,255,255,0.02);
  }

  .inp-group {
    display: flex;
    flex-direction: column;
    gap: 3px;
    flex: 1;
    min-width: 120px;
  }

  .inp-group label {
    font-size: 11px;
    color: var(--text3);
    font-family: var(--mono);
  }

  .prog-input {
    background: var(--bg2);
    border: 1px solid rgba(255,255,255,0.08);
    border-radius: 6px;
    padding: 7px 10px;
    font-family: var(--mono);
    font-size: 12px;
    color: var(--text);
    outline: none;
    transition: border-color 0.2s;
    width: 100%;
  }

  .prog-input:focus { border-color: rgba(0,212,255,0.4); }

  .prog-footer {
    padding: 0.75rem 1rem;
    display: flex;
    align-items: center;
    justify-content: space-between;
    gap: 1rem;
    border-top: 1px solid rgba(255,255,255,0.05);
  }

  .run-btn {
    font-family: var(--mono);
    font-size: 12px;
    padding: 8px 20px;
    border-radius: 999px;
    border: none;
    background: var(--accent);
    color: #000;
    font-weight: 700;
    cursor: pointer;
    letter-spacing: 0.05em;
    transition: all 0.2s;
  }

  .run-btn:hover { opacity: 0.85; transform: scale(0.98); }

  .output-box {
    flex: 1;
    background: var(--bg2);
    border: 1px solid rgba(255,255,255,0.06);
    border-radius: 6px;
    padding: 8px 12px;
    font-family: var(--mono);
    font-size: 12px;
    color: var(--accent3);
    min-height: 38px;
    white-space: pre-wrap;
    word-break: break-all;
  }

  /* ====== SECTION HEADER ====== */
  .section-label {
    font-family: var(--mono);
    font-size: 11px;
    letter-spacing: 0.15em;
    color: var(--text3);
    text-transform: uppercase;
    margin-bottom: 1rem;
    margin-top: 0.5rem;
  }

  /* animations */
  @keyframes fadeIn {
    from { opacity: 0; transform: translateY(8px); }
    to { opacity: 1; transform: translateY(0); }
  }

  .unit-card { animation: fadeIn 0.3s ease both; }
  .unit-card:nth-child(1) { animation-delay: 0s; }
  .unit-card:nth-child(2) { animation-delay: 0.05s; }
  .unit-card:nth-child(3) { animation-delay: 0.1s; }
  .unit-card:nth-child(4) { animation-delay: 0.15s; }
  .unit-card:nth-child(5) { animation-delay: 0.2s; }
  .unit-card:nth-child(6) { animation-delay: 0.25s; }
</style>
</head>
<body>

<!-- HEADER -->
<header class="site-header">
  <div class="tag">Ingeniería · Matemáticas</div>
  <h1>Métodos<br><span>Numéricos</span></h1>
  <p>Unidades, subtemas y programas interactivos para comprender y aplicar los métodos numéricos.</p>
  <div class="header-stats">
    <div class="stat"><div class="stat-n">6</div><div class="stat-l">Unidades</div></div>
    <div class="stat"><div class="stat-n">28</div><div class="stat-l">Subtemas</div></div>
    <div class="stat"><div class="stat-n">15+</div><div class="stat-l">Programas</div></div>
  </div>
</header>

<!-- NAV -->
<nav class="nav-wrap">
  <div class="nav-inner">
    <button class="nav-btn active" onclick="showOverview()">▦ Todas</button>
    <button class="nav-btn" onclick="showUnit(1)">U1 · Introducción</button>
    <button class="nav-btn" onclick="showUnit(2)">U2 · Ecuaciones</button>
    <button class="nav-btn" onclick="showUnit(3)">U3 · Sistemas</button>
    <button class="nav-btn" onclick="showUnit(4)">U4 · Difer. e Integr.</button>
    <button class="nav-btn" onclick="showUnit(5)">U5 · Interpolación</button>
    <button class="nav-btn" onclick="showUnit(6)">U6 · Ec. Diferenciales</button>
  </div>
</nav>

<div class="main">

  <!-- ===== OVERVIEW ===== -->
  <div id="overview-view">
    <p class="section-label">Selecciona una unidad para explorar</p>
    <div class="unit-grid">

      <div class="unit-card" style="--c:#00d4ff" onclick="showUnit(1)">
        <div class="unit-num">UNIDAD 01</div>
        <div class="unit-title">Introducción a los Métodos Numéricos</div>
        <div class="unit-subtemas-preview">
          <div class="preview-item">Importancia de los métodos numéricos</div>
          <div class="preview-item">Cifras significativas, precisión, exactitud</div>
          <div class="preview-item">Tipos de errores</div>
          <div class="preview-item">Software de cómputo numérico</div>
          <div class="preview-item">Métodos iterativos</div>
        </div>
        <div class="unit-footer">
          <span class="badge" style="border-color:rgba(0,212,255,0.3);color:#00d4ff">5 subtemas</span>
          <span class="open-arrow">→</span>
        </div>
      </div>

      <div class="unit-card" style="--c:#7c3aed" onclick="showUnit(2)">
        <div class="unit-num">UNIDAD 02</div>
        <div class="unit-title">Métodos de Solución de Ecuaciones</div>
        <div class="unit-subtemas-preview">
          <div class="preview-item">Métodos de intervalo</div>
          <div class="preview-item">Método de bisección</div>
          <div class="preview-item">Aproximaciones sucesivas</div>
          <div class="preview-item">Métodos de interpolación</div>
          <div class="preview-item">Aplicaciones</div>
        </div>
        <div class="unit-footer">
          <span class="badge" style="border-color:rgba(124,58,237,0.3);color:#7c3aed">5 subtemas</span>
          <span class="open-arrow">→</span>
        </div>
      </div>

      <div class="unit-card" style="--c:#10b981" onclick="showUnit(3)">
        <div class="unit-num">UNIDAD 03</div>
        <div class="unit-title">Métodos de Solución de Sistemas de Ecuaciones</div>
        <div class="unit-subtemas-preview">
          <div class="preview-item">Métodos iterativos</div>
          <div class="preview-item">Sistemas no lineales</div>
          <div class="preview-item">Iteración y convergencia</div>
          <div class="preview-item">Aplicaciones</div>
        </div>
        <div class="unit-footer">
          <span class="badge" style="border-color:rgba(16,185,129,0.3);color:#10b981">4 subtemas</span>
          <span class="open-arrow">→</span>
        </div>
      </div>

      <div class="unit-card" style="--c:#f59e0b" onclick="showUnit(4)">
        <div class="unit-num">UNIDAD 04</div>
        <div class="unit-title">Diferenciación e Integración Numérica</div>
        <div class="unit-subtemas-preview">
          <div class="preview-item">Diferenciación numérica</div>
          <div class="preview-item">Integración numérica</div>
          <div class="preview-item">Integración múltiple</div>
          <div class="preview-item">Aplicaciones</div>
        </div>
        <div class="unit-footer">
          <span class="badge" style="border-color:rgba(245,158,11,0.3);color:#f59e0b">4 subtemas</span>
          <span class="open-arrow">→</span>
        </div>
      </div>

      <div class="unit-card" style="--c:#ef4444" onclick="showUnit(5)">
        <div class="unit-num">UNIDAD 05</div>
        <div class="unit-title">Interpolación y Ajuste de Funciones</div>
        <div class="unit-subtemas-preview">
          <div class="preview-item">Polinomio de Newton</div>
          <div class="preview-item">Polinomio de Lagrange</div>
          <div class="preview-item">Interpolación segmentada</div>
          <div class="preview-item">Regresión y mínimos cuadrados</div>
        </div>
        <div class="unit-footer">
          <span class="badge" style="border-color:rgba(239,68,68,0.3);color:#ef4444">6 subtemas</span>
          <span class="open-arrow">→</span>
        </div>
      </div>

      <div class="unit-card" style="--c:#ec4899" onclick="showUnit(6)">
        <div class="unit-num">UNIDAD 06</div>
        <div class="unit-title">Solución de Ecuaciones Diferenciales</div>
        <div class="unit-subtemas-preview">
          <div class="preview-item">Métodos de paso</div>
          <div class="preview-item">Método de pasos múltiples</div>
          <div class="preview-item">Sistemas de EDOs</div>
          <div class="preview-item">Aplicaciones</div>
        </div>
        <div class="unit-footer">
          <span class="badge" style="border-color:rgba(236,72,153,0.3);color:#ec4899">4 subtemas</span>
          <span class="open-arrow">→</span>
        </div>
      </div>

    </div>
  </div>

  <!-- ===== UNIT 1 ===== -->
  <div class="unit-detail" id="unit-1">
    <div class="detail-header">
      <button class="back-btn" onclick="showOverview()">← Volver</button>
      <div class="detail-title-wrap">
        <h2 style="color:#00d4ff">Unidad 1</h2>
        <p>Introducción a los Métodos Numéricos</p>
      </div>
    </div>
    <div class="subtemas-list">

      <!-- 1.1 -->
      <div class="subtema-block" style="--c:#00d4ff">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">1.1</span>
          <span class="subtema-name">Importancia de los métodos numéricos</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Los métodos numéricos son técnicas mediante las cuales es posible formular problemas matemáticos de tal forma que puedan resolverse usando operaciones aritméticas. Son fundamentales en ingeniería y ciencias porque la mayoría de los problemas reales no tienen solución analítica exacta o son demasiado complejos para resolverse por métodos algebraicos tradicionales.</p>
        </div>
      </div>

      <!-- 1.2 -->
      <div class="subtema-block" style="--c:#00d4ff">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">1.2</span>
          <span class="subtema-name">Cifra significativa, precisión, exactitud, incertidumbre y sesgo</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria"><strong>Cifras significativas:</strong> Son los dígitos confiables de un número. <strong>Precisión</strong> se refiere a cuán cercanos están entre sí varios valores medidos. <strong>Exactitud</strong> indica cuán cercano está un valor calculado del valor verdadero. El <strong>error</strong> puede ser absoluto o relativo.</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ error_relativo.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Cálculo de error absoluto y relativo</span>
<span class="kw">def</span> <span class="fn">calcular_errores</span>(v_verdadero, v_aproximado):
    e_abs = <span class="fn">abs</span>(v_verdadero - v_aproximado)
    e_rel = (e_abs / <span class="fn">abs</span>(v_verdadero)) * <span class="nm">100</span>
    <span class="kw">return</span> e_abs, e_rel</div>
            <div class="prog-inputs">
              <div class="inp-group"><label>Valor verdadero</label><input class="prog-input" id="p12a" type="number" value="3.14159" placeholder="ej: 3.14159"></div>
              <div class="inp-group"><label>Valor aproximado</label><input class="prog-input" id="p12b" type="number" value="3.14" placeholder="ej: 3.14"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run12()">▶ Ejecutar</button>
              <div class="output-box" id="out12">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

      <!-- 1.3 -->
      <div class="subtema-block" style="--c:#00d4ff">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">1.3</span>
          <span class="subtema-name">Tipo de errores</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Los errores numéricos surgen del uso de aproximaciones para representar operaciones y cantidades matemáticas exactas. Los tipos principales son: <strong>Error de truncamiento</strong> (por truncar una serie infinita), <strong>Error de redondeo</strong> (por la representación finita de números), y <strong>Error inherente</strong> (en los datos de entrada).</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ error_truncamiento.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Aproximación de e^x con serie de Taylor</span>
<span class="kw">import</span> math
<span class="kw">def</span> <span class="fn">taylor_exp</span>(x, n_terminos):
    resultado = <span class="nm">0</span>
    <span class="kw">for</span> i <span class="kw">in</span> <span class="fn">range</span>(n_terminos):
        resultado += (x**i) / <span class="fn">math.factorial</span>(i)
    <span class="kw">return</span> resultado</div>
            <div class="prog-inputs">
              <div class="inp-group"><label>Valor de x</label><input class="prog-input" id="p13a" type="number" value="2" placeholder="ej: 2"></div>
              <div class="inp-group"><label>Nº de términos</label><input class="prog-input" id="p13b" type="number" value="5" placeholder="ej: 5"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run13()">▶ Ejecutar</button>
              <div class="output-box" id="out13">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

      <!-- 1.4 -->
      <div class="subtema-block" style="--c:#00d4ff">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">1.4</span>
          <span class="subtema-name">Software de cómputo numérico</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Los principales softwares para métodos numéricos incluyen: <strong>MATLAB</strong> (el más usado en ingeniería), <strong>Python</strong> con las librerías NumPy, SciPy y Matplotlib, <strong>Octave</strong> (alternativa gratuita a MATLAB), y <strong>Mathematica</strong>. En este curso usaremos Python por ser gratuito y ampliamente utilizado en la industria.</p>
        </div>
      </div>

      <!-- 1.5 -->
      <div class="subtema-block" style="--c:#00d4ff">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">1.5</span>
          <span class="subtema-name">Métodos iterativos</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Un método iterativo genera una sucesión de aproximaciones que convergen a la solución. Se parte de una estimación inicial y se refina repetidamente hasta alcanzar la precisión deseada. El criterio de parada suele ser un error relativo menor que una tolerancia ε.</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ raiz_cuadrada_iterativa.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Raíz cuadrada por método iterativo (Newton)</span>
<span class="kw">def</span> <span class="fn">raiz_iterativa</span>(n, tol=<span class="nm">1e-6</span>):
    x = n / <span class="nm">2</span>
    iteraciones = <span class="nm">0</span>
    <span class="kw">while True</span>:
        x_nuevo = (x + n/x) / <span class="nm">2</span>
        iteraciones += <span class="nm">1</span>
        <span class="kw">if</span> <span class="fn">abs</span>(x_nuevo - x) &lt; tol: <span class="kw">break</span>
        x = x_nuevo
    <span class="kw">return</span> x_nuevo, iteraciones</div>
            <div class="prog-inputs">
              <div class="inp-group"><label>Número</label><input class="prog-input" id="p15a" type="number" value="25" placeholder="ej: 25"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run15()">▶ Ejecutar</button>
              <div class="output-box" id="out15">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

    </div>
  </div>

  <!-- ===== UNIT 2 ===== -->
  <div class="unit-detail" id="unit-2">
    <div class="detail-header">
      <button class="back-btn" onclick="showOverview()">← Volver</button>
      <div class="detail-title-wrap">
        <h2 style="color:#7c3aed">Unidad 2</h2>
        <p>Métodos de Solución de Ecuaciones</p>
      </div>
    </div>
    <div class="subtemas-list">

      <div class="subtema-block" style="--c:#7c3aed">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">2.1</span>
          <span class="subtema-name">Métodos de intervalo</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Los métodos de intervalo (o métodos de acotación) se basan en el teorema de valor intermedio: si f(a) y f(b) tienen signos opuestos, existe al menos una raíz en [a,b]. Garantizan convergencia pero pueden ser lentos. Ejemplos: bisección y regla falsa.</p>
        </div>
      </div>

      <div class="subtema-block" style="--c:#7c3aed">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">2.2</span>
          <span class="subtema-name">Método de bisección</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">El método de bisección divide repetidamente el intervalo [a,b] a la mitad y selecciona el subintervalo donde ocurre el cambio de signo. Es robusto y siempre converge, aunque lentamente. Requiere aproximadamente log₂((b-a)/ε) iteraciones.</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ biseccion.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Método de bisección para f(x) = x³ - x - 2</span>
<span class="kw">def</span> <span class="fn">f</span>(x):
    <span class="kw">return</span> x**<span class="nm">3</span> - x - <span class="nm">2</span>

<span class="kw">def</span> <span class="fn">biseccion</span>(a, b, tol=<span class="nm">0.001</span>):
    iters = []
    <span class="kw">while</span> (b - a) / <span class="nm">2</span> &gt; tol:
        c = (a + b) / <span class="nm">2</span>
        iters.append(c)
        <span class="kw">if</span> <span class="fn">f</span>(c) == <span class="nm">0</span>: <span class="kw">break</span>
        <span class="kw">elif</span> <span class="fn">f</span>(a) * <span class="fn">f</span>(c) &lt; <span class="nm">0</span>: b = c
        <span class="kw">else</span>: a = c
    <span class="kw">return</span> (a+b)/<span class="nm">2</span>, <span class="fn">len</span>(iters)</div>
            <div class="prog-inputs">
              <div class="inp-group"><label>Límite a</label><input class="prog-input" id="p22a" type="number" value="1"></div>
              <div class="inp-group"><label>Límite b</label><input class="prog-input" id="p22b" type="number" value="2"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run22()">▶ Ejecutar</button>
              <div class="output-box" id="out22">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

      <div class="subtema-block" style="--c:#7c3aed">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">2.3</span>
          <span class="subtema-name">Método de aproximaciones sucesivas</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">También llamado método de punto fijo. Se reescribe f(x)=0 como x=g(x) y se itera xₙ₊₁=g(xₙ). Converge si |g'(x)|&lt;1 en el intervalo. El método de Newton-Raphson es una variante de punto fijo de convergencia cuadrática.</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ newton_raphson.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Newton-Raphson para f(x) = x² - N (raíz de N)</span>
<span class="kw">def</span> <span class="fn">newton</span>(N, x0, tol=<span class="nm">1e-6</span>):
    x = x0
    <span class="kw">for</span> i <span class="kw">in</span> <span class="fn">range</span>(<span class="nm">100</span>):
        fx = x**<span class="nm">2</span> - N
        dfx = <span class="nm">2</span>*x
        x_new = x - fx/dfx
        <span class="kw">if</span> <span class="fn">abs</span>(x_new - x) &lt; tol:
            <span class="kw">return</span> x_new, i+<span class="nm">1</span>
        x = x_new</div>
            <div class="prog-inputs">
              <div class="inp-group"><label>N (encontrar √N)</label><input class="prog-input" id="p23a" type="number" value="9"></div>
              <div class="inp-group"><label>Estimación inicial x₀</label><input class="prog-input" id="p23b" type="number" value="3"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run23()">▶ Ejecutar</button>
              <div class="output-box" id="out23">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

      <div class="subtema-block" style="--c:#7c3aed">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">2.4</span>
          <span class="subtema-name">Métodos de interpolación</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">La interpolación es el proceso de estimar valores intermedios entre puntos discretos de datos. La regla falsa (Regula Falsi) es un método de intervalo que usa interpolación lineal para estimar la raíz: c = b - f(b)(b-a)/(f(b)-f(a)).</p>
        </div>
      </div>

      <div class="subtema-block" style="--c:#7c3aed">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">2.5</span>
          <span class="subtema-name">Aplicaciones</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Aplicación práctica: encontrar la tasa de interés de un préstamo. Dado un préstamo P, n pagos mensuales de pago A, encontrar la tasa mensual i que satisface la ecuación financiera usando bisección.</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ aplicacion_prestamo.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Calcular el monto final con interés compuesto</span>
<span class="kw">def</span> <span class="fn">interes_compuesto</span>(P, r, n):
    <span class="st">"""P=capital, r=tasa anual (%), n=años"""</span>
    <span class="kw">return</span> P * (<span class="nm">1</span> + r/<span class="nm">100</span>)**n</div>
            <div class="prog-inputs">
              <div class="inp-group"><label>Capital P ($)</label><input class="prog-input" id="p25a" type="number" value="10000"></div>
              <div class="inp-group"><label>Tasa anual (%)</label><input class="prog-input" id="p25b" type="number" value="5"></div>
              <div class="inp-group"><label>Años n</label><input class="prog-input" id="p25c" type="number" value="10"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run25()">▶ Ejecutar</button>
              <div class="output-box" id="out25">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

    </div>
  </div>

  <!-- ===== UNIT 3 ===== -->
  <div class="unit-detail" id="unit-3">
    <div class="detail-header">
      <button class="back-btn" onclick="showOverview()">← Volver</button>
      <div class="detail-title-wrap">
        <h2 style="color:#10b981">Unidad 3</h2>
        <p>Métodos de Solución de Sistemas de Ecuaciones</p>
      </div>
    </div>
    <div class="subtemas-list">

      <div class="subtema-block" style="--c:#10b981">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">3.1</span>
          <span class="subtema-name">Métodos iterativos</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Los métodos iterativos para sistemas de ecuaciones lineales incluyen <strong>Jacobi</strong> y <strong>Gauss-Seidel</strong>. Jacobi actualiza todas las variables usando los valores de la iteración anterior. Gauss-Seidel usa los valores más recientes disponibles, convergiendo más rápido.</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ gauss_seidel.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Gauss-Seidel: 4x+y=9, x+3y=7</span>
<span class="kw">def</span> <span class="fn">gauss_seidel</span>(tol=<span class="nm">0.001</span>):
    x, y = <span class="nm">0</span>, <span class="nm">0</span>
    <span class="kw">for</span> i <span class="kw">in</span> <span class="fn">range</span>(<span class="nm">50</span>):
        x_n = (<span class="nm">9</span> - y) / <span class="nm">4</span>
        y_n = (<span class="nm">7</span> - x_n) / <span class="nm">3</span>
        <span class="kw">if</span> <span class="fn">abs</span>(x_n-x) + <span class="fn">abs</span>(y_n-y) &lt; tol:
            <span class="kw">return</span> x_n, y_n, i+<span class="nm">1</span>
        x, y = x_n, y_n</div>
            <div class="prog-footer" style="padding-top:0.75rem">
              <button class="run-btn" onclick="run31()">▶ Ejecutar</button>
              <div class="output-box" id="out31">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

      <div class="subtema-block" style="--c:#10b981">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">3.2</span>
          <span class="subtema-name">Sistemas de ecuaciones no lineales</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Para sistemas de ecuaciones no lineales F(x)=0, se generaliza Newton-Raphson usando la matriz Jacobiana J(x). La iteración es xₙ₊₁ = xₙ - J⁻¹(xₙ)F(xₙ). Requiere resolver un sistema lineal en cada iteración, lo que puede ser costoso computacionalmente.</p>
        </div>
      </div>

      <div class="subtema-block" style="--c:#10b981">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">3.3</span>
          <span class="subtema-name">Iteración y convergencia de sistemas</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">La convergencia de métodos iterativos para sistemas depende del radio espectral de la matriz de iteración. Para Jacobi y Gauss-Seidel, la condición suficiente es que la matriz sea diagonal dominante: |aᵢᵢ| &gt; Σⱼ≠ᵢ|aᵢⱼ|.</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ diagonal_dominante.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Verificar diagonal dominante de una matriz 2x2</span>
<span class="kw">def</span> <span class="fn">es_diagonal_dominante</span>(a11, a12, a21, a22):
    fila1 = <span class="fn">abs</span>(a11) &gt; <span class="fn">abs</span>(a12)
    fila2 = <span class="fn">abs</span>(a22) &gt; <span class="fn">abs</span>(a21)
    <span class="kw">return</span> fila1 <span class="kw">and</span> fila2</div>
            <div class="prog-inputs">
              <div class="inp-group"><label>a11</label><input class="prog-input" id="p33a" type="number" value="4"></div>
              <div class="inp-group"><label>a12</label><input class="prog-input" id="p33b" type="number" value="1"></div>
              <div class="inp-group"><label>a21</label><input class="prog-input" id="p33c" type="number" value="1"></div>
              <div class="inp-group"><label>a22</label><input class="prog-input" id="p33d" type="number" value="3"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run33()">▶ Ejecutar</button>
              <div class="output-box" id="out33">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

      <div class="subtema-block" style="--c:#10b981">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">3.4</span>
          <span class="subtema-name">Aplicaciones</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Los sistemas de ecuaciones aparecen en: análisis de circuitos eléctricos (leyes de Kirchhoff), análisis de estructuras (método de rigidez), redes de fluidos, modelos económicos de insumo-producto (modelo de Leontief), y simulaciones de fluidos computacionales (CFD).</p>
        </div>
      </div>

    </div>
  </div>

  <!-- ===== UNIT 4 ===== -->
  <div class="unit-detail" id="unit-4">
    <div class="detail-header">
      <button class="back-btn" onclick="showOverview()">← Volver</button>
      <div class="detail-title-wrap">
        <h2 style="color:#f59e0b">Unidad 4</h2>
        <p>Diferenciación e Integración Numérica</p>
      </div>
    </div>
    <div class="subtemas-list">

      <div class="subtema-block" style="--c:#f59e0b">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">4.1</span>
          <span class="subtema-name">Diferenciación numérica</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">La diferenciación numérica aproxima derivadas mediante diferencias finitas. Las fórmulas principales son: <strong>Hacia adelante</strong>: f'(x) ≈ [f(x+h)-f(x)]/h, <strong>Hacia atrás</strong>: f'(x) ≈ [f(x)-f(x-h)]/h, <strong>Centrada</strong>: f'(x) ≈ [f(x+h)-f(x-h)]/(2h), con error O(h²).</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ diferenciacion_numerica.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Diferenciación de f(x) = x² en un punto</span>
<span class="kw">def</span> <span class="fn">derivada_centrada</span>(f, x, h=<span class="nm">0.001</span>):
    <span class="kw">return</span> (f(x+h) - f(x-h)) / (<span class="nm">2</span>*h)

<span class="kw">def</span> <span class="fn">f</span>(x): <span class="kw">return</span> x**<span class="nm">2</span>
<span class="cm"># Derivada exacta de x² en x=a es 2a</span></div>
            <div class="prog-inputs">
              <div class="inp-group"><label>Punto x</label><input class="prog-input" id="p41a" type="number" value="3"></div>
              <div class="inp-group"><label>Paso h</label><input class="prog-input" id="p41b" type="number" value="0.001" step="0.001"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run41()">▶ Ejecutar</button>
              <div class="output-box" id="out41">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

      <div class="subtema-block" style="--c:#f59e0b">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">4.2</span>
          <span class="subtema-name">Integración numérica</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Los métodos de integración numérica aproximan ∫f(x)dx. <strong>Regla del trapecio</strong>: divide el área bajo la curva en trapecios. <strong>Regla de Simpson 1/3</strong>: usa polinomios cuadráticos, con error O(h⁴), más precisa. <strong>Regla de Simpson 3/8</strong>: usa polinomios cúbicos.</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ simpson.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Integración de f(x)=x² con regla de Simpson</span>
<span class="kw">def</span> <span class="fn">simpson_13</span>(a, b, n=<span class="nm">100</span>):
    <span class="kw">if</span> n % <span class="nm">2</span> != <span class="nm">0</span>: n += <span class="nm">1</span>
    h = (b - a) / n
    xs = [a + i*h <span class="kw">for</span> i <span class="kw">in</span> <span class="fn">range</span>(n+<span class="nm">1</span>)]
    ys = [x**<span class="nm">2</span> <span class="kw">for</span> x <span class="kw">in</span> xs]
    s = ys[<span class="nm">0</span>] + ys[-<span class="nm">1</span>]
    s += <span class="nm">4</span>*<span class="fn">sum</span>(ys[<span class="nm">1</span>::<span class="nm">2</span>]) + <span class="nm">2</span>*<span class="fn">sum</span>(ys[<span class="nm">2</span>:-<span class="nm">1</span>:<span class="nm">2</span>])
    <span class="kw">return</span> h*s/<span class="nm">3</span></div>
            <div class="prog-inputs">
              <div class="inp-group"><label>Límite a</label><input class="prog-input" id="p42a" type="number" value="0"></div>
              <div class="inp-group"><label>Límite b</label><input class="prog-input" id="p42b" type="number" value="3"></div>
              <div class="inp-group"><label>Subintervalos n</label><input class="prog-input" id="p42c" type="number" value="100"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run42()">▶ Ejecutar</button>
              <div class="output-box" id="out42">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

      <div class="subtema-block" style="--c:#f59e0b">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">4.3</span>
          <span class="subtema-name">Integración múltiple</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">La integración múltiple extiende los métodos univariados. Para doble integral ∬f(x,y)dxdy se aplica integración numérica sucesivamente: primero sobre x para cada y fijo, luego sobre y. La cuadratura de Gauss en 2D es eficiente para regiones regulares.</p>
        </div>
      </div>

      <div class="subtema-block" style="--c:#f59e0b">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">4.4</span>
          <span class="subtema-name">Aplicaciones</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Aplicaciones de integración numérica: cálculo de trabajo en física (W=∫F·dx), centros de masa de figuras irregulares, análisis espectral de señales (transformada de Fourier discreta), cálculo de probabilidades en distribuciones continuas, y dinámica de fluidos.</p>
        </div>
      </div>

    </div>
  </div>

  <!-- ===== UNIT 5 ===== -->
  <div class="unit-detail" id="unit-5">
    <div class="detail-header">
      <button class="back-btn" onclick="showOverview()">← Volver</button>
      <div class="detail-title-wrap">
        <h2 style="color:#ef4444">Unidad 5</h2>
        <p>Interpolación y Ajuste de Funciones</p>
      </div>
    </div>
    <div class="subtemas-list">

      <div class="subtema-block" style="--c:#ef4444">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">5.1</span>
          <span class="subtema-name">Polinomio de interpolación de Newton</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">El polinomio de Newton usa diferencias divididas para construir un polinomio interpolador. Tiene la ventaja de que añadir un nuevo punto solo requiere agregar un término. La forma es: P(x) = [y₀] + [y₀,y₁](x-x₀) + [y₀,y₁,y₂](x-x₀)(x-x₁) + ...</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ newton_interpolacion.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Interpolación de Newton con 3 puntos</span>
<span class="kw">def</span> <span class="fn">newton_interp</span>(xs, ys, x_eval):
    n = <span class="fn">len</span>(xs)
    dd = [y <span class="kw">for</span> y <span class="kw">in</span> ys]
    coefs = [dd[<span class="nm">0</span>]]
    <span class="kw">for</span> j <span class="kw">in</span> <span class="fn">range</span>(<span class="nm">1</span>, n):
        <span class="kw">for</span> i <span class="kw">in</span> <span class="fn">range</span>(n-j-<span class="nm">1</span>, -<span class="nm">1</span>, -<span class="nm">1</span>):
            dd[i] = (dd[i+<span class="nm">1</span>]-dd[i])/(xs[i+j]-xs[i])
        coefs.append(dd[<span class="nm">0</span>])
    result = coefs[-<span class="nm">1</span>]
    <span class="kw">for</span> k <span class="kw">in</span> <span class="fn">range</span>(n-<span class="nm">2</span>, -<span class="nm">1</span>, -<span class="nm">1</span>):
        result = result*(x_eval-xs[k]) + coefs[k]
    <span class="kw">return</span> result</div>
            <div class="prog-inputs">
              <div class="inp-group"><label>x₁, y₁</label><input class="prog-input" id="p51a" placeholder="1, 1"></div>
              <div class="inp-group"><label>x₂, y₂</label><input class="prog-input" id="p51b" placeholder="2, 4"></div>
              <div class="inp-group"><label>x₃, y₃</label><input class="prog-input" id="p51c" placeholder="3, 9"></div>
              <div class="inp-group"><label>Evaluar en x=</label><input class="prog-input" id="p51d" type="number" value="2.5"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run51()">▶ Ejecutar</button>
              <div class="output-box" id="out51">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

      <div class="subtema-block" style="--c:#ef4444">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">5.2</span>
          <span class="subtema-name">Polinomio de interpolación de Lagrange</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">El polinomio de Lagrange expresa P(x) como combinación lineal de polinomios base Lᵢ(x). Cada Lᵢ(x) vale 1 en xᵢ y 0 en los demás nodos. Es equivalente al de Newton pero con diferente forma: P(x) = Σᵢ yᵢLᵢ(x).</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ lagrange.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Interpolación de Lagrange con 3 puntos</span>
<span class="kw">def</span> <span class="fn">lagrange</span>(xs, ys, x):
    n = <span class="fn">len</span>(xs)
    total = <span class="nm">0</span>
    <span class="kw">for</span> i <span class="kw">in</span> <span class="fn">range</span>(n):
        Li = <span class="nm">1</span>
        <span class="kw">for</span> j <span class="kw">in</span> <span class="fn">range</span>(n):
            <span class="kw">if</span> i != j:
                Li *= (x - xs[j]) / (xs[i] - xs[j])
        total += ys[i] * Li
    <span class="kw">return</span> total</div>
            <div class="prog-inputs">
              <div class="inp-group"><label>x₁, y₁</label><input class="prog-input" id="p52a" placeholder="0, 1"></div>
              <div class="inp-group"><label>x₂, y₂</label><input class="prog-input" id="p52b" placeholder="1, 2.718"></div>
              <div class="inp-group"><label>x₃, y₃</label><input class="prog-input" id="p52c" placeholder="2, 7.389"></div>
              <div class="inp-group"><label>Evaluar en x=</label><input class="prog-input" id="p52d" type="number" value="0.5"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run52()">▶ Ejecutar</button>
              <div class="output-box" id="out52">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

      <div class="subtema-block" style="--c:#ef4444">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">5.3</span>
          <span class="subtema-name">Interpolación segmentada</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">En lugar de usar un solo polinomio de alto grado (que puede oscilar), la interpolación segmentada usa polinomios de bajo grado en cada subintervalo. Los <strong>splines cúbicos</strong> son la forma más popular: polinomios cúbicos que garantizan continuidad de f, f' y f'' en los nodos.</p>
        </div>
      </div>

      <div class="subtema-block" style="--c:#ef4444">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">5.4</span>
          <span class="subtema-name">Regresión y correlación</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">La regresión ajusta una función a un conjunto de datos ruidosos (no necesariamente pasando por los puntos). El coeficiente de correlación de Pearson r mide la fuerza de la relación lineal. r=±1 indica correlación perfecta, r=0 indica ausencia de correlación lineal.</p>
        </div>
      </div>

      <div class="subtema-block" style="--c:#ef4444">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">5.5</span>
          <span class="subtema-name">Mínimos cuadrados</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">El método de mínimos cuadrados minimiza la suma de los cuadrados de los residuales. Para regresión lineal y=ax+b, las ecuaciones normales son: a=(nΣxy-ΣxΣy)/(nΣx²-(Σx)²), b=(Σy-aΣx)/n.</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ minimos_cuadrados.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Regresión lineal por mínimos cuadrados</span>
<span class="kw">def</span> <span class="fn">min_cuadrados</span>(xs, ys):
    n = <span class="fn">len</span>(xs)
    sx = <span class="fn">sum</span>(xs); sy = <span class="fn">sum</span>(ys)
    sxy = <span class="fn">sum</span>(x*y <span class="kw">for</span> x,y <span class="kw">in</span> <span class="fn">zip</span>(xs,ys))
    sx2 = <span class="fn">sum</span>(x**<span class="nm">2</span> <span class="kw">for</span> x <span class="kw">in</span> xs)
    a = (n*sxy - sx*sy) / (n*sx2 - sx**<span class="nm">2</span>)
    b = (sy - a*sx) / n
    <span class="kw">return</span> a, b</div>
            <div class="prog-inputs">
              <div class="inp-group" style="flex:2;min-width:200px"><label>Puntos x (separados por comas)</label><input class="prog-input" id="p55a" value="1,2,3,4,5"></div>
              <div class="inp-group" style="flex:2;min-width:200px"><label>Puntos y (separados por comas)</label><input class="prog-input" id="p55b" value="2.1,3.9,6.2,7.8,10.1"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run55()">▶ Ejecutar</button>
              <div class="output-box" id="out55">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

      <div class="subtema-block" style="--c:#ef4444">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">5.6</span>
          <span class="subtema-name">Problemas de aplicación</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">La interpolación y regresión se aplican en: predicción de series de tiempo (economía, meteorología), procesamiento de imágenes (escalado bicúbico), diseño CAD/CAM con splines, análisis de datos experimentales en física y química, y calibración de sensores e instrumentos de medición.</p>
        </div>
      </div>

    </div>
  </div>

  <!-- ===== UNIT 6 ===== -->
  <div class="unit-detail" id="unit-6">
    <div class="detail-header">
      <button class="back-btn" onclick="showOverview()">← Volver</button>
      <div class="detail-title-wrap">
        <h2 style="color:#ec4899">Unidad 6</h2>
        <p>Solución de Ecuaciones Diferenciales</p>
      </div>
    </div>
    <div class="subtemas-list">

      <div class="subtema-block" style="--c:#ec4899">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">6.1</span>
          <span class="subtema-name">Métodos de paso</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Los métodos de paso único calculan yₙ₊₁ usando solo información de yₙ. El más simple es el <strong>método de Euler</strong>: yₙ₊₁ = yₙ + h·f(xₙ,yₙ). El método de <strong>Runge-Kutta de 4° orden (RK4)</strong> es el más popular por su precisión y estabilidad, con error O(h⁴).</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ euler.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># Método de Euler para dy/dx = y, y(0)=1</span>
<span class="cm"># Solución exacta: y = e^x</span>
<span class="kw">def</span> <span class="fn">euler</span>(x0, y0, xf, h):
    x, y = x0, y0
    pasos = []
    <span class="kw">while</span> x &lt;= xf:
        pasos.append((x, y))
        y = y + h * y  <span class="cm"># f(x,y) = y</span>
        x = x + h
    <span class="kw">return</span> pasos</div>
            <div class="prog-inputs">
              <div class="inp-group"><label>x final</label><input class="prog-input" id="p61a" type="number" value="1"></div>
              <div class="inp-group"><label>Paso h</label><input class="prog-input" id="p61b" type="number" value="0.1" step="0.05"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run61()">▶ Ejecutar</button>
              <div class="output-box" id="out61">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

      <div class="subtema-block" style="--c:#ec4899">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">6.2</span>
          <span class="subtema-name">Método de pasos múltiples</span>
          <span class="has-prog">Programa</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Los métodos de pasos múltiples usan información de varios puntos anteriores para calcular el siguiente. El método de <strong>Adams-Bashforth</strong> es el predictor y <strong>Adams-Moulton</strong> es el corrector. Son más eficientes que RK4 por requerir menos evaluaciones de la función por paso.</p>
          <div class="prog-widget">
            <div class="prog-top-bar">
              <span class="prog-label">▶ runge_kutta4.py</span>
              <div class="dots"><div class="dot" style="background:#ef4444"></div><div class="dot" style="background:#f59e0b"></div><div class="dot" style="background:#10b981"></div></div>
            </div>
            <div class="code-area"><span class="cm"># RK4 para dy/dx = -2xy, y(0) = 1</span>
<span class="cm"># Solución exacta: y = e^(-x²)</span>
<span class="kw">def</span> <span class="fn">f</span>(x, y): <span class="kw">return</span> -<span class="nm">2</span>*x*y

<span class="kw">def</span> <span class="fn">rk4</span>(x0, y0, xf, h):
    x, y = x0, y0
    <span class="kw">while</span> x &lt; xf:
        k1 = h*<span class="fn">f</span>(x, y)
        k2 = h*<span class="fn">f</span>(x+h/<span class="nm">2</span>, y+k1/<span class="nm">2</span>)
        k3 = h*<span class="fn">f</span>(x+h/<span class="nm">2</span>, y+k2/<span class="nm">2</span>)
        k4 = h*<span class="fn">f</span>(x+h, y+k3)
        y += (k1+<span class="nm">2</span>*k2+<span class="nm">2</span>*k3+k4)/<span class="nm">6</span>
        x += h
    <span class="kw">return</span> x, y</div>
            <div class="prog-inputs">
              <div class="inp-group"><label>x final</label><input class="prog-input" id="p62a" type="number" value="1"></div>
              <div class="inp-group"><label>Paso h</label><input class="prog-input" id="p62b" type="number" value="0.1" step="0.05"></div>
            </div>
            <div class="prog-footer">
              <button class="run-btn" onclick="run62()">▶ Ejecutar</button>
              <div class="output-box" id="out62">Esperando...</div>
            </div>
          </div>
        </div>
      </div>

      <div class="subtema-block" style="--c:#ec4899">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">6.3</span>
          <span class="subtema-name">Sistemas de ecuaciones diferenciales ordinarias</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Los sistemas de EDOs surgen naturalmente en dinámica: un péndulo, un circuito RLC, modelos depredador-presa (Lotka-Volterra). Se resuelven aplicando métodos de paso a cada ecuación simultáneamente. RK4 se extiende fácilmente a sistemas vectoriales y es el estándar.</p>
        </div>
      </div>

      <div class="subtema-block" style="--c:#ec4899">
        <div class="subtema-header" onclick="toggle(this)">
          <span class="subtema-num">6.4</span>
          <span class="subtema-name">Aplicaciones</span>
          <span class="chevron">▾</span>
        </div>
        <div class="subtema-body">
          <p class="teoria">Las ecuaciones diferenciales se aplican en: simulación de circuitos eléctricos, dinámica de estructuras y sismos, transferencia de calor transiente, modelado de epidemias (SIR), trayectorias de proyectiles, y control de sistemas mecánicos y robóticos.</p>
        </div>
      </div>

    </div>
  </div>

</div><!-- end main -->

<script>
// ============ NAVIGATION ============
function showOverview() {
  document.getElementById('overview-view').style.display = 'block';
  document.querySelectorAll('.unit-detail').forEach(d => d.classList.remove('active'));
  document.querySelectorAll('.nav-btn').forEach((b,i) => b.classList.toggle('active', i===0));
}

function showUnit(n) {
  document.getElementById('overview-view').style.display = 'none';
  document.querySelectorAll('.unit-detail').forEach(d => d.classList.remove('active'));
  document.getElementById('unit-'+n).classList.add('active');
  document.querySelectorAll('.nav-btn').forEach((b,i) => b.classList.toggle('active', i===n));
  window.scrollTo({top:0,behavior:'smooth'});
}

// ============ ACCORDION ============
function toggle(header) {
  const block = header.parentElement;
  block.classList.toggle('open');
}

// ============ PROGRAMS ============
function v(id) { return document.getElementById(id).value; }
function out(id, text) { document.getElementById(id).textContent = text; }

function run12() {
  const a = parseFloat(v('p12a')), b = parseFloat(v('p12b'));
  if(isNaN(a)||isNaN(b)||a===0){out('out12','Error: valores inválidos');return;}
  const eAbs = Math.abs(a-b);
  const eRel = (eAbs/Math.abs(a))*100;
  out('out12', `Error absoluto: ${eAbs.toFixed(6)}\nError relativo: ${eRel.toFixed(4)} %`);
}

function run13() {
  const x = parseFloat(v('p13a')), n = parseInt(v('p13b'));
  if(isNaN(x)||isNaN(n)||n<1){out('out13','Error: valores inválidos');return;}
  let result = 0, fact = 1;
  for(let i=0;i<n;i++){
    if(i>0) fact*=i;
    result += Math.pow(x,i)/fact;
  }
  const exact = Math.exp(x);
  out('out13', `Aprox (${n} términos): ${result.toFixed(8)}\nValor exacto e^${x}: ${exact.toFixed(8)}\nError: ${Math.abs(exact-result).toFixed(8)}`);
}

function run15() {
  const n = parseFloat(v('p15a'));
  if(isNaN(n)||n<=0){out('out15','Error: número debe ser positivo');return;}
  let x = n/2, iters = 0;
  while(true){
    const xn = (x + n/x)/2; iters++;
    if(Math.abs(xn-x)<1e-10) break;
    x = xn;
  }
  out('out15', `√${n} ≈ ${x.toFixed(10)}\nExacto: ${Math.sqrt(n).toFixed(10)}\nIteraciones: ${iters}`);
}

function run22() {
  const a0=parseFloat(v('p22a')), b0=parseFloat(v('p22b'));
  function f(x){return x*x*x-x-2;}
  if(f(a0)*f(b0)>0){out('out22','No hay cambio de signo en [a,b]');return;}
  let a=a0,b=b0,iters=0;
  while((b-a)/2>0.0001&&iters<100){
    const c=(a+b)/2; iters++;
    if(f(c)===0) break;
    else if(f(a)*f(c)<0) b=c;
    else a=c;
  }
  const root=(a+b)/2;
  out('out22', `Raíz ≈ ${root.toFixed(6)}\nf(raíz) = ${f(root).toFixed(8)}\nIteraciones: ${iters}`);
}

function run23() {
  const N=parseFloat(v('p23a')), x0=parseFloat(v('p23b'));
  if(isNaN(N)||N<0){out('out23','N debe ser positivo');return;}
  let x=x0, iters=0;
  for(let i=0;i<100;i++){
    const xn=x-(x*x-N)/(2*x); iters++;
    if(Math.abs(xn-x)<1e-10){x=xn;break;}
    x=xn;
  }
  out('out23', `√${N} ≈ ${x.toFixed(10)}\nVerificación: ${x.toFixed(6)}² = ${(x*x).toFixed(6)}\nIteraciones: ${iters}`);
}

function run25() {
  const P=parseFloat(v('p25a')), r=parseFloat(v('p25b')), n=parseInt(v('p25c'));
  if(isNaN(P)||isNaN(r)||isNaN(n)){out('out25','Valores inválidos');return;}
  const total = P*Math.pow(1+r/100,n);
  const ganancia = total - P;
  out('out25', `Capital final: $${total.toFixed(2)}\nCapital inicial: $${P.toFixed(2)}\nGanancia: $${ganancia.toFixed(2)}`);
}

function run31() {
  let x=0,y=0,iters=0;
  for(let i=0;i<50;i++){
    const xn=(9-y)/4, yn=(7-xn)/3; iters++;
    if(Math.abs(xn-x)+Math.abs(yn-y)<0.0001){x=xn;y=yn;break;}
    x=xn;y=yn;
  }
  out('out31', `x = ${x.toFixed(6)}\ny = ${y.toFixed(6)}\nVerif: 4(${x.toFixed(3)})+${y.toFixed(3)} = ${(4*x+y).toFixed(4)} ≈ 9\nIter: ${iters}`);
}

function run33() {
  const a=parseFloat(v('p33a')),b=parseFloat(v('p33b')),c=parseFloat(v('p33c')),d=parseFloat(v('p33d'));
  const f1=Math.abs(a)>Math.abs(b), f2=Math.abs(d)>Math.abs(c);
  out('out33', `Fila 1: |${a}| > |${b}| → ${f1?'✓':'✗'}\nFila 2: |${d}| > |${c}| → ${f2?'✓':'✗'}\n${f1&&f2?'✓ Diagonal dominante: converge':'✗ No garantiza convergencia'}`);
}

function run41() {
  const x=parseFloat(v('p41a')), h=parseFloat(v('p41b'))||0.001;
  const aprox = ((x+h)*(x+h)-(x-h)*(x-h))/(2*h);
  const exacto = 2*x;
  out('out41', `f(x) = x²  →  f'(x) = 2x\nNumérica: ${aprox.toFixed(8)}\nExacta: ${exacto.toFixed(8)}\nError: ${Math.abs(aprox-exacto).toExponential(2)}`);
}

function run42() {
  const a=parseFloat(v('p42a')),b=parseFloat(v('p42b'));
  let n=parseInt(v('p42c'))||100;
  if(n%2!==0)n++;
  const h=(b-a)/n;
  const xs=Array.from({length:n+1},(_,i)=>a+i*h);
  const ys=xs.map(x=>x*x);
  let s=ys[0]+ys[n];
  for(let i=1;i<n;i++) s+=(i%2===0?2:4)*ys[i];
  const result=h*s/3;
  const exact=(b*b*b-a*a*a)/3;
  out('out42', `∫x² dx de ${a} a ${b}\nSimpson: ${result.toFixed(8)}\nExacto: ${exact.toFixed(8)}\nError: ${Math.abs(result-exact).toExponential(2)}`);
}

function parsePoint(str){
  const p=str.split(',').map(s=>parseFloat(s.trim()));
  if(p.length===2&&!isNaN(p[0])&&!isNaN(p[1])) return p;
  return null;
}

function run51() {
  const p1=parsePoint(v('p51a')),p2=parsePoint(v('p51b')),p3=parsePoint(v('p51c'));
  const xe=parseFloat(v('p51d'));
  if(!p1||!p2||!p3||isNaN(xe)){out('out51','Formato: x, y (ej: 1, 1)');return;}
  const xs=[p1[0],p2[0],p3[0]],ys=[p1[1],p2[1],p3[1]];
  const dd=[...ys];
  const coefs=[dd[0]];
  for(let j=1;j<3;j++){
    for(let i=2-j;i>=0;i--)
      dd[i]=(dd[i+1]-dd[i])/(xs[i+j]-xs[i]);
    coefs.push(dd[0]);
  }
  let r=coefs[2];
  r=r*(xe-xs[1])+coefs[1];
  r=r*(xe-xs[0])+coefs[0];
  out('out51', `P(${xe}) ≈ ${r.toFixed(6)}\n(Usando puntos: (${xs.join(',')}), (${ys.join(',')}))`);
}

function run52() {
  const p1=parsePoint(v('p52a')),p2=parsePoint(v('p52b')),p3=parsePoint(v('p52c'));
  const xe=parseFloat(v('p52d'));
  if(!p1||!p2||!p3||isNaN(xe)){out('out52','Formato: x, y (ej: 0, 1)');return;}
  const xs=[p1[0],p2[0],p3[0]],ys=[p1[1],p2[1],p3[1]];
  let total=0;
  for(let i=0;i<3;i++){
    let Li=1;
    for(let j=0;j<3;j++) if(i!==j) Li*=(xe-xs[j])/(xs[i]-xs[j]);
    total+=ys[i]*Li;
  }
  out('out52', `P(${xe}) ≈ ${total.toFixed(6)}\ne^${xe} exacto ≈ ${Math.exp(xe).toFixed(6)}`);
}

function run55() {
  const xs=v('p55a').split(',').map(s=>parseFloat(s.trim()));
  const ys=v('p55b').split(',').map(s=>parseFloat(s.trim()));
  if(xs.length!==ys.length||xs.some(isNaN)||ys.some(isNaN)){out('out55','Misma cantidad de puntos x e y');return;}
  const n=xs.length;
  const sx=xs.reduce((a,b)=>a+b,0),sy=ys.reduce((a,b)=>a+b,0);
  const sxy=xs.reduce((s,x,i)=>s+x*ys[i],0);
  const sx2=xs.reduce((s,x)=>s+x*x,0);
  const a=(n*sxy-sx*sy)/(n*sx2-sx*sx);
  const b=(sy-a*sx)/n;
  out('out55', `Regresión: y = ${a.toFixed(4)}x + ${b.toFixed(4)}\nPendiente a = ${a.toFixed(4)}\nIntercepto b = ${b.toFixed(4)}`);
}

function run61() {
  const xf=parseFloat(v('p61a')), h=parseFloat(v('p61b'))||0.1;
  let x=0,y=1,steps=0;
  while(x<xf-1e-9){ y+=h*y; x+=h; steps++; }
  const exact=Math.exp(xf);
  out('out61', `Euler: y(${xf}) ≈ ${y.toFixed(8)}\nExacto e^${xf} = ${exact.toFixed(8)}\nError: ${Math.abs(y-exact).toExponential(2)}\nPasos: ${steps}`);
}

function run62() {
  const xf=parseFloat(v('p62a')), h=parseFloat(v('p62b'))||0.1;
  function f(x,y){return -2*x*y;}
  let x=0,y=1;
  while(x<xf-1e-9){
    const k1=h*f(x,y),k2=h*f(x+h/2,y+k1/2);
    const k3=h*f(x+h/2,y+k2/2),k4=h*f(x+h,y+k3);
    y+=(k1+2*k2+2*k3+k4)/6; x+=h;
  }
  const exact=Math.exp(-xf*xf);
  out('out62', `RK4: y(${xf}) ≈ ${y.toFixed(10)}\nExacto e^(-${xf}²) = ${exact.toFixed(10)}\nError: ${Math.abs(y-exact).toExponential(2)}`);
}
</script>

</body>
</html>
