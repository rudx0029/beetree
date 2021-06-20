#!/usr/bin/env python3
import json
import sys
import argparse
import os


def log(msg):
    print("make-registry: " + msg)


def open_manifest(fpath):
    '''
    Opens a JSON file containing the definition of a register bank.

    Parameters
    ----------

    ``fpath``
        The path of the JSON file

    Returns
    -------

    A JSON object representing the register bank.
    '''
    j = None
    
    log("Loading manifest from " + fpath)
    with open(fpath, 'r') as infile:
        j = json.load(infile)

    if not j:
        raise Exception("json is not found or invalid for " + fpath)
    if not "name" in j:
        raise Exception("json is not found or invalid for " + fpath)
    if not "version" in j:
        raise Exception("json is not found or invalid for " + fpath)
    if not "items" in j:
        raise Exception("json is not found or invalid for " + fpath)
    return j



def create_registry_item(tab, item):
    item_str = []

    item_str.append(tab + "/**\n")
    item_str.append(tab + " * {}\n".format(item["desc"]))
    item_str.append(tab + " * type: {}\n".format(item["type"]))
    item_str.append(tab + " */\n")
    item_str.append(tab + item["tag"] + ',\n')
    return ''.join(item_str)


def create_registry_bank(namespace, register):
    registerTitle = register["name"]
    registerKeys = registerTitle + 'Keys'
    registerBank = registerTitle + 'RegisterBank'

    header = []
    tab = '    '
    header.append('#pragma once')
    header.append('')
    header.append('//--------------------------------------------')
    header.append('//')
    header.append('// This file is auto-generated. Do not modify!')
    header.append('// version {}'.format(register['version']))
    header.append('//')
    header.append('//--------------------------------------------')
    header.append('')
    header.append('#include "beetree/platform/basics/banks.hpp"')
    header.append('')
    header.append('namespace {}'.format(namespace))
    header.append('{')
    header.append(tab + 'enum class {}'.format(registerKeys))
    header.append(tab + '{')
    for item in register['items']:
        header.append(create_registry_item(tab + tab, item))
    header.append(tab + tab + 'NUM_ITEMS')

    header.append(tab + '};')
    header.append(
        tab + 'using {} = bte::registry::Bank<{}>;'.format(registerBank, registerKeys))
    header.append('}')

    return '\n'.join(header)


def create_registry_types(namespace, registers):
    '''
    Params
    ------

    ``namespace``
        C++ namespace the registers belong to
    
    ``registers``
        A list of names of the registers
    '''
    header = []
    tab = '    '
    header.append('#pragma once\n')
    header.append('\n')
    header.append('//--------------------------------------------\n')
    header.append('//\n')
    header.append('// This file is auto-generated. Do not modify!\n')
    header.append('//\n')
    header.append('//--------------------------------------------\n')
    header.append('\n')
    header.append('namespace {}\n'.format(namespace))
    header.append('{\n')
    header.append(tab + 'enum class RegisterBankType\n')
    header.append(tab + '{\n')

    for register in registers:
        header.append(tab + tab + register + ',\n')
    header.append(tab + tab + 'NUM_BANKS\n')

    header.append(tab + '};\n')
    header.append('}\n')

    return ''.join(header)

def create_registry_index(registers):
    '''
    Params
    ------
    
    ``registers``
        A list of names of the registers
    '''
    return {
        "index":registers
    }





def make_registry(namespace, out_dir, index_path, register_paths):
    '''
    Generates c++ headers and data structures representing the register banks 
    specified in the given manifest.

    For each JSON file defining a register bank, the tool generates a corresponding
    C++ header file containing the register bank's data structure for use in the 
    BeeTree environment. After generating each register banks' header, the tool 
    generates a C++ registry bank enumeration in a header file named 
    ``register-bank-type.hpp``. The enumeration is used for indexing into the set
    of register banks. All of the header files are generated in the 
    directory ``out_dir``. Finally, a JSON file is generated at the path 
    ``index_path`` containing the index of the registry banks for use with BeeView.

    .. seealso:: docs/7-registry.md

    Parameters
    ----------

    ``namespace``
        The C++ namespace that the register bank data structures and constants
        belong to.

    ``out_dir``
        The directory to generate the header files in.

    ``index_path``
        The generated JSON file containing the index of the register banks with 
        respect to the generated enumeration in ``register-bank-type.hpp``

    ``register_paths``
        One or more JSON files describing a register bank.

    Command Line Usage
    ------------------

    Given a registry for the *simplebee* application with the following parameters:

     * namespace is ``simplebee``
     * the desired output directory is ``${CMAKE_CURRENT_BINARY_DIR}/include/simplebee/registry``
     * the desired index path is ``${CMAKE_CURRENT_BINARY_DIR}/simplebee-registry-index.json``
     * there are two register banks defined: 
        * ${CMAKE_CURRENT_SOURCE_DIR}/registry/nav-register-bank.json
        * ${CMAKE_CURRENT_SOURCE_DIR}/registry/diag-register-bank.json

    We can generate the header files and other generated source with the following command    
    ::
        
        > [python] make-registry.py --namespace simplebee \\
            --out_dir ${CMAKE_CURRENT_BINARY_DIR}/include/simplebee/registry \\
            --index_path ${CMAKE_CURRENT_BINARY_DIR}/simplebee-registry-index.json \\           
            --registers \\
            ${CMAKE_CURRENT_SOURCE_DIR}/registry/nav-register-bank.json \\
            ${CMAKE_CURRENT_SOURCE_DIR}/registry/diag-register-bank.json

    The headers generated are

     * ``${CMAKE_CURRENT_BINARY_DIR}/include/simplebee/registry/nav-register-bank.hpp``
     * ``${CMAKE_CURRENT_BINARY_DIR}/include/simplebee/registry/diag-register-bank.hpp``
     * ``${CMAKE_CURRENT_BINARY_DIR}/include/simplebee/registry/register-bank-type.hpp``

    The JSON index is generated at

     * ``${CMAKE_CURRENT_BINARY_DIR}/simplebee-registry-index.json``

    '''
    os.makedirs(os.path.abspath(out_dir), exist_ok=True)
    os.makedirs(os.path.abspath(os.path.dirname(index_path)), exist_ok=True)

    # generate each registry bank
    os.path.split
    registers = [{'register':open_manifest(os.path.abspath(p)),'path':p} for p in register_paths]
    for register in registers:
        bank = create_registry_bank(namespace, register['register'])

        # prepare the path for the register bank header
        register_base = os.path.splitext(os.path.basename(register["path"]))[0]
        register_out = os.path.join(out_dir, register_base + '.hpp') 

        # remove existing files
        try:
            os.remove(os.path.abspath(register_out))
        except:
            pass

        with open(os.path.abspath(register_out), 'w') as outfile:
            outfile.write(bank)
            log("Generated {}".format(os.path.abspath(register_out)))

    # generate the registry types and index
    register_names = [r['register']['name'] for r in registers]
    index = create_registry_index(register_names)
    types = create_registry_types(namespace, register_names)
    types_path = os.path.join(out_dir, "register-bank-type.hpp")

    with open(os.path.abspath(types_path), 'w') as outfile:
        outfile.write(types)
        log("Generated {}".format(types_path))

    with open(os.path.abspath(index_path), 'w') as outfile:
        json.dump(index, outfile)
        log("Generated {}".format(index_path))

    log("Goodbye!")


if __name__ == "__main__":
    description = \
        "Creates one or more registry bank header definitions along " \
        "with the register bank type enumeration when given one or " \
        "more JSON files defining the registry bank."

    parser = argparse.ArgumentParser(description=description)

    requiredNamed = parser.add_argument_group('required named arguments')
    requiredNamed.add_argument(
        '-n', '--namespace', help="the namespace the register banks will belong to", required=True)
    requiredNamed.add_argument('-o', '--out_dir',
                        help="output directory for the genereated register bank headers", required=True)
    requiredNamed.add_argument('-i','--index_path',
                        help="path for the generated JSON registry index, e.g. path/to/my-registry-index.json", required=True)
    requiredNamed.add_argument('-r', '--registers', nargs="+",
                        help="one or more JSON registry paths. e.g. path/to/my-register-bank.json")

    args = parser.parse_args()

    make_registry(args.namespace, args.out_dir, args.index_path, args.registers)
