/* Sonic Heroes Decompilation: shared site script.
   - live progress from the tracker (ByteMatch first, decomp.dev as fallback);
     the numbers already in the HTML are the last known values, so the page
     reads correctly without JavaScript or when both trackers are down
   - mobile menu
   - a one-line language suggestion (never an automatic redirect) */
(function () {
  "use strict";
  var pt = (document.documentElement.lang || "").toLowerCase().indexOf("pt") === 0;
  var T = pt
    ? { live: "Ao vivo do ", down: "Dados ao vivo indisponíveis; números da última atualização", upd: "Atualizado em ", fns: " funções", units: " unidades", bytes: " bytes" }
    : { live: "Live from ", down: "Live data unavailable; showing the last published numbers", upd: "Updated ", fns: " functions", units: " units", bytes: " bytes" };
  var SOURCES = [
    { name: "ByteMatch", url: "https://bytematch.dev/Jovinull/sonicheroes.json" },
    { name: "decomp.dev", url: "https://decomp.dev/Jovinull/sonicheroes.json" }
  ];
  var locale = pt ? "pt-BR" : "en-US";

  function store(key, val) {
    try {
      if (val === undefined) return window.localStorage.getItem(key);
      window.localStorage.setItem(key, val);
    } catch (e) { return null; }
    return null;
  }
  function q(sel, root) { return (root || document).querySelector(sel); }
  function qa(sel, root) { return Array.prototype.slice.call((root || document).querySelectorAll(sel)); }
  function fmtInt(n) { return (n || 0).toLocaleString(locale); }
  function fmtPct(v) { return v.toLocaleString(locale, { minimumFractionDigits: v < 10 ? 2 : 1, maximumFractionDigits: v < 10 ? 2 : 1 }); }

  function setStat(scope, key, pctValue, absText) {
    var n = q('[data-num="' + key + '"]', scope);
    if (n) n.textContent = fmtPct(pctValue);
    var a = q('[data-abs="' + key + '"]', scope);
    if (a && absText) a.textContent = absText;
    var b = q('[data-bar="' + key + '"]', scope);
    if (b) {
      var w = Math.max(Math.min(pctValue, 100), pctValue > 0 ? 1 : 0);
      b.style.width = w + "%";
      if (b.parentNode) b.parentNode.setAttribute("aria-valuenow", pctValue.toFixed(2));
    }
  }

  function apply(m, scope) {
    var units = m.total_units ? (m.complete_units || 0) * 100 / m.total_units : 0;
    setStat(scope, "code", m.matched_code_percent || 0, fmtInt(m.matched_code) + " / " + fmtInt(m.total_code) + T.bytes);
    setStat(scope, "data", m.matched_data_percent || 0, fmtInt(m.matched_data) + " / " + fmtInt(m.total_data) + T.bytes);
    setStat(scope, "fn", m.matched_functions_percent || 0, fmtInt(m.matched_functions) + " / " + fmtInt(m.total_functions) + T.fns);
    setStat(scope, "units", units, fmtInt(m.complete_units) + " / " + fmtInt(m.total_units) + T.units);
  }

  function render(j, source) {
    apply(j.measures || {}, document);
    (j.report_categories || []).forEach(function (c) {
      var card = q('[data-cat="' + c.id + '"]');
      if (card && c.measures) apply(c.measures, card);
    });
    var label = q("#live-label");
    if (label) label.textContent = T.live + source;
    if (j.commit) {
      var commit = q("#commit");
      if (commit) {
        commit.textContent = j.commit.sha.slice(0, 7) + " · " + (j.commit.message || "").split("\n")[0].slice(0, 60);
        commit.setAttribute("href", "https://github.com/Jovinull/sonicheroes/commit/" + j.commit.sha);
      }
      var upd = q("#updated");
      if (upd && j.commit.timestamp) upd.textContent = T.upd + new Date(j.commit.timestamp).toLocaleDateString(locale, { year: "numeric", month: "short", day: "numeric" });
    }
  }

  function load(i) {
    if (!q("[data-num]")) return;
    if (i >= SOURCES.length) {
      var label = q("#live-label");
      if (label) label.textContent = T.down;
      return;
    }
    var s = SOURCES[i];
    fetch(s.url, { cache: "no-store" })
      .then(function (r) { if (!r.ok) throw new Error(r.status); return r.json(); })
      .then(function (j) { if (!j.measures) throw new Error("no measures"); render(j, s.name); })
      .catch(function () { load(i + 1); });
  }

  function menu() {
    var btn = q(".menu-btn"), nav = q(".nav");
    if (!btn || !nav) return;
    btn.addEventListener("click", function () {
      var open = nav.classList.toggle("open");
      btn.setAttribute("aria-expanded", open ? "true" : "false");
    });
  }

  function langHint() {
    var bar = q(".langbar");
    if (!bar || store("sh-lang-hint") === "off") return;
    var langs = (navigator.languages && navigator.languages.length ? navigator.languages : [navigator.language || ""]).join(",").toLowerCase();
    var wantsPt = /(^|,)pt/.test(langs);
    if ((wantsPt && !pt) || (!wantsPt && pt)) bar.classList.add("show");
    var close = q("button", bar);
    if (close) close.addEventListener("click", function () { bar.classList.remove("show"); store("sh-lang-hint", "off"); });
    qa("a", bar).forEach(function (a) { a.addEventListener("click", function () { store("sh-lang-hint", "off"); }); });
  }

  menu();
  langHint();
  load(0);
  if (q("[data-num]")) setInterval(function () { load(0); }, 120000);
})();
