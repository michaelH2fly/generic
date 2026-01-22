#from generation_hal.generate_hal import parse_components_from_definition_directory
#from generation_generic.generate_generic import parse_generic_functions_from_definition_files

import yaml
import data_models


path_generation_config = "config_generation.yaml"

def load_generation_config():

    with open(path_generation_config, 'r') as file:

        config_generation = yaml.safe_load(file)

    return config_generation

def main():

    
    # load generation config
    config = load_generation_config()

    # parse data from yaml files
    #component_data      = parse_components_from_definition_directory(config["paths"]["definition_components"])
    #generic_functions   = parse_generic_functions_from_definition_files(config["paths"]["definition_generic_functions"])



if __name__ == "__main__":

    main()