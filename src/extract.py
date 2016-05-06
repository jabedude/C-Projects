#!/usr/bin/python

import sys
import os
import pefile

SC_SECTION = "sccode"

def gen_test_header():
    s = """
#include <stdio.h>
#include <windows.h>
"""
    return s

def gen_test_footer():
    s = """
typedef void (*sc_entry_t)();
int main(void) {
    sc_entry_t sc_entry;
    PVOID p = VirtualAlloc(NULL, sizeof(shellcode),
        MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (p == NULL) {
        printf("VirtualAlloc failed: %d\\n", GetLastError());
    }
    memcpy(p, shellcode, sizeof(shellcode));
    sc_entry = (sc_entry_t) p;
    printf("jumping to shellcode @ %p\\n", p);
    sc_entry();
    printf("done\\n");
    return 0;
}
"""
    return s

def find_sc_section(pe, find_name):
    for section in pe.sections:
        #print (i, section.Name, hex(section.VirtualAddress),
        #        hex(section.SizeOfRawData), hex(section.Misc_VirtualSize))
        secname = section.Name.replace("\x00","")
        if secname == find_name:
            return section
    return None

def bin2array(buf, name):
    s = ""
    s += "// %u bytes\n" % (len(buf))
    s += "unsigned char %s[%u] = {\n" % (name, len(buf))
    for i in xrange(len(buf)):
        if i > 0 and i % 12 == 0:
            s += "\n"
        s += "0x%02X" % (ord(buf[i]))
        if i < len(buf) - 1:
            s += ","
    s += "\n};\n"
    return s

def usage(prog):
    print "usage: %s [--testharness] <exe>" % (prog)

def main(argv):
    i = 1
    generate_test = False

    if not len(argv) in [2,3]:
        usage(argv[0])
        return 1

    if argv[i] == '--testharness':
        generate_test = True
        i += 1

    pe = pefile.PE(argv[i])
    section = find_sc_section(pe, SC_SECTION)
    if not section:
        print "error: couldn't find section %s in the binary" % (SC_SECTION)
        return 2

    scbuf = section.get_data()[:section.Misc_VirtualSize]

    if generate_test:
        print gen_test_header()
    print bin2array(scbuf, "shellcode")
    if generate_test:
        print gen_test_footer()
    return 0

if __name__ == "__main__":
    sys.exit(main(sys.argv))

