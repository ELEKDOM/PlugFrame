#!/usr/bin/env bash
set -euo pipefail

SYSROOT="${1:-}"
if [[ -z "${SYSROOT}" ]]; then
  echo "Usage: $0 /path/to/sysroot"
  exit 1
fi

LIBCSO="${SYSROOT}/usr/lib/aarch64-linux-gnu/libc.so"

if [[ ! -f "${LIBCSO}" ]]; then
  echo "ERROR: libc.so not found: ${LIBCSO}"
  exit 1
fi

# Detect if already patched (no absolute /lib or /usr/lib paths)
if grep -qE 'GROUP \( libc\.so\.6 libc_nonshared\.a' "${LIBCSO}"; then
  echo "OK: libc.so already patched"
else
  echo "Patching: ${LIBCSO}"
  cp -a "${LIBCSO}" "${LIBCSO}.bak"

  sed -i \
    -e 's|/lib/aarch64-linux-gnu/libc.so.6|libc.so.6|g' \
    -e 's|/usr/lib/aarch64-linux-gnu/libc_nonshared.a|libc_nonshared.a|g' \
    -e 's|/lib/ld-linux-aarch64.so.1|ld-linux-aarch64.so.1|g' \
    "${LIBCSO}"
fi

# Ensure libc_nonshared.a is findable from lib/ too (optional but robust)
if [[ -f "${SYSROOT}/usr/lib/aarch64-linux-gnu/libc_nonshared.a" ]]; then
  mkdir -p "${SYSROOT}/lib/aarch64-linux-gnu"
  ln -sf "../../usr/lib/aarch64-linux-gnu/libc_nonshared.a" \
    "${SYSROOT}/lib/aarch64-linux-gnu/libc_nonshared.a"
fi

echo "Result:"
grep -n 'GROUP' "${LIBCSO}" || true

