#!/usr/bin/env bash
# ==========================================================
# make_flamegraph.sh — profile your game and generate flamegraph.svg
# Saves all profiling files under ./profile/
# ==========================================================

set -e

GAME_BIN="./bin/game"
FLAMEGRAPH_DIR="$HOME/.gitfiles/FlameGraph"
PROFILE_DIR="./profile"
PERF_FREQ=99

# --- Create output directory ---
mkdir -p "$PROFILE_DIR"

PERF_DATA="$PROFILE_DIR/perf.data"
PERF_SCRIPT_OUT="$PROFILE_DIR/out.perf"
FOLDED_OUT="$PROFILE_DIR/out.folded"
SVG_OUT="$PROFILE_DIR/flamegraph.svg"

# --- Check dependencies ---
for cmd in perf perl; do
    if ! command -v "$cmd" &>/dev/null; then
        echo "❌ Missing required command: $cmd"
        exit 1
    fi
done

for script in "$FLAMEGRAPH_DIR/stackcollapse-perf.pl" "$FLAMEGRAPH_DIR/flamegraph.pl"; do
    if [[ ! -f "$script" ]]; then
        echo "❌ Missing FlameGraph script: $script"
        echo "Make sure you cloned https://github.com/brendangregg/FlameGraph into $FLAMEGRAPH_DIR"
        exit 1
    fi
done

# --- Ensure game binary exists ---
if [[ ! -f "$GAME_BIN" ]]; then
    echo "❌ Game binary not found at $GAME_BIN"
    exit 1
fi

# --- Check and adjust perf_event_paranoid ---
PARANOID=$(cat /proc/sys/kernel/perf_event_paranoid)
if [[ "$PARANOID" -gt 1 ]]; then
    echo "⚠️  perf_event_paranoid=$PARANOID — lowering to 0 (requires sudo)"
    sudo sh -c 'echo 0 > /proc/sys/kernel/perf_event_paranoid'
fi

# --- Record performance data ---
echo "🎮 Running $GAME_BIN under perf..."
perf record -F $PERF_FREQ --call-graph dwarf -o "$PERF_DATA" -- "$GAME_BIN"

# --- Convert perf data into readable stacks ---
echo "🧩 Generating stack traces..."
perf script -i "$PERF_DATA" > "$PERF_SCRIPT_OUT"

if [[ ! -s "$PERF_SCRIPT_OUT" ]]; then
    echo "❌ perf script output empty — no samples recorded."
    echo "Try running the game longer or checking perf permissions."
    exit 1
fi

# --- Collapse and render flame graph ---
echo "🔥 Collapsing stacks..."
"$FLAMEGRAPH_DIR/stackcollapse-perf.pl" "$PERF_SCRIPT_OUT" > "$FOLDED_OUT"

if [[ ! -s "$FOLDED_OUT" ]]; then
    echo "❌ Collapsed output empty — stack capture failed."
    exit 1
fi

echo "📊 Rendering flame graph..."
"$FLAMEGRAPH_DIR/flamegraph.pl" "$FOLDED_OUT" > "$SVG_OUT"

if [[ -f "$SVG_OUT" ]]; then
    echo "✅ Flame graph generated: $SVG_OUT"
    echo "📁 All profiling data saved in: $PROFILE_DIR"
    if command -v xdg-open &>/dev/null; then
      firefox "$SVG_OUT" >/dev/null 2>&1 &
    fi
else
    echo "❌ Failed to generate $SVG_OUT"
    exit 1
fi
