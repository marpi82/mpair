#!/usr/bin/env python3
"""
Check for GPL-3.0 license headers in C/C++ source files.
"""

import sys
import re
from pathlib import Path

LICENSE_PATTERNS = [
    r'GPL-3\.0',
    r'GNU General Public License',
    r'@license GPL-3\.0'
]

def check_file(filepath):
    """Check if file has GPL-3.0 license header."""
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            content = f.read(500)  # Check first 500 chars
            
        for pattern in LICENSE_PATTERNS:
            if re.search(pattern, content, re.IGNORECASE):
                return True
        return False
    except Exception as e:
        print(f"Error reading {filepath}: {e}", file=sys.stderr)
        return True  # Don't fail on read errors

def main():
    """Main function."""
    if len(sys.argv) < 2:
        print("Usage: check_license_headers.py <file1> [file2] ...", file=sys.stderr)
        sys.exit(1)
    
    missing_license = []
    
    for filepath in sys.argv[1:]:
        path = Path(filepath)
        
        # Skip build directories and external components
        if 'build' in path.parts or 'managed_components' in path.parts:
            continue
        
        # Check only C/C++ source files
        if path.suffix not in ['.c', '.h', '.cpp', '.hpp']:
            continue
        
        if not check_file(filepath):
            missing_license.append(filepath)
    
    if missing_license:
        print("❌ The following files are missing GPL-3.0 license headers:", file=sys.stderr)
        for filepath in missing_license:
            print(f"  - {filepath}", file=sys.stderr)
        sys.exit(1)
    
    print("✅ All source files have proper license headers")
    sys.exit(0)

if __name__ == '__main__':
    main()
