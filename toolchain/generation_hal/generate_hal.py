import yaml
from pathlib import Path

file_config_hal_generation = "config_hal_generation.yaml"


def load_config_hal_generation():

    with open(file_config_hal_generation, 'r') as file:

        config_hal_generation = yaml.safe_load(file)

    return config_hal_generation
    
def parse_component_definition_files():

    # load the configuration for the hal generation

    config_hal_generation = load_config_hal_generation()
    print(config_hal_generation)
    print(config_hal_generation["paths"]["definition_components"])

    component_definition_paths = config_hal_generation["paths"]["definition_components"]

    parsed_data = {}

    for comp_def_path in component_definition_paths:

        comp_def_path = Path(comp_def_path)

        if not comp_def_path.is_dir():
            print(f"Warning: {comp_def_path} is not a directory, skipping.")
            continue
        
        for suffix in ["*.yaml", ".yml"]:

            for yaml_file in comp_def_path.rglob(suffix):
                try:
                    with yaml_file.open("r", encoding="utf-8") as f:
                        parsed_data[str(yaml_file)] = yaml.safe_load(f)
                except Exception as e:
                    print(f"Failed to parse {yaml_file}: {e}")

        
    return parsed_data


if __name__ == "__main__":

    parsed_data = parse_component_definition_files()

    print(parsed_data)
