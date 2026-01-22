from pathlib import Path
import yaml

def parse_data_from_yaml_to_data_model(dirs, data_model_type) -> list:

    # init list
    data_model_list = []

    # loop over directories
    for dir in dirs:

        dir = Path(dir)

        # ignore not exisiting directories
        if not dirs.is_dir():
            print(f"warning: {dirs} does not exist")
            continue

        # loop over different yaml suffixes
        for suffix in ["*.yaml", "*.yml"]:

            #loop over all files in the directory with respecitve suffix
            for yaml_file in dir.rglob(suffix):

                try: 
                    #open the file with reading permission
                    with yaml_file.open("r", encoding="UTF-8") as f:
                        
                        try:
                            raw_data = yaml.safe_load(f)
                            parsed_data_model = data_model_type(**raw_data)
                            data_model_list.append(parsed_data_model)

                            print(f"Info: parsed component")
                            
                        except Exception as e:
                            print(f"Unexpected error reading %s", {e})

                except Exception as e:
                    print(f"Failed to parse {yaml_file}: {e}")

    return data_model_list
