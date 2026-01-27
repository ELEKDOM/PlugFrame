#!/usr/bin/env bash
set -euo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"
export LD_LIBRARY_PATH="$SCRIPT_DIR/../libs:/usr/local/Qt/current/lib:${LD_LIBRARY_PATH:-}"
exec "$SCRIPT_DIR/plugframe_guilauncher-qt6" "$@"


