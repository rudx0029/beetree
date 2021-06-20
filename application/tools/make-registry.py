import importlib  
import argparse
mr = importlib.import_module("make-registry-v1")

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
                        help="output directory for the generated register bank headers", required=True)
    requiredNamed.add_argument('-i','--index_path',
                        help="path for the generated JSON registry index, e.g. path/to/my-registry-index.json", required=True)
    requiredNamed.add_argument('-r', '--registers', nargs="+",
                        help="one or more JSON registry paths. e.g. path/to/my-register-bank.json")

    args = parser.parse_args()

    mr.make_registry(args.namespace, args.out_dir, args.index_path, args.registers)