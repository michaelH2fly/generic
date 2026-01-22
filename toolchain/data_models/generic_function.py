from pydantic import BaseModel
from enum import Enum
from typing import List

class PhysicalSymbol(str,Enum):
    n = "n"
    p = "p"
    T = "T"
    U = "U"
    I = "I"
    mpt = "mpt"

class Unit(str, Enum):
    rpm     = "rpm"
    bar     = "bar"
    bara    = "bara"
    degC    = "degC"
    K       = "K"
    V       = "V"
    A       = "A"
    mA      = "mA"
    gps     = "gps"

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

class GenericFunctionList(BaseModel):
    generic_functions: List[GenericFunction]



