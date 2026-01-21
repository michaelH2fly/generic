from pydantic import BaseModel
from enum import Enum

class PhysicalSymbol(str,Enum):
    n = "n"
    p = "p"
    T = "T"
    U = "U"
    I = "I"

class Unit(str, Enum):
    rpm     = "rpm"
    bar     = "bar"
    bara    = "bara"
    degC    = "degC"
    K       = "K"
    V       = "V"
    A       = "A"
    mA      = "mA"

class GenericFunctionType(str, Enum):
    input = "input"
    output = "output"

class GenericFunction(BaseModel):
    name: str
    abbrev: str
    symbol: PhysicalSymbol
    unit: Unit
    function_type: GenericFunctionType
    description: str




