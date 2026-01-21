from pydantic import BaseModel


class GenericComponent(BaseModel):
    name: str    
    feedback_signals: list
    command_signals: list

    