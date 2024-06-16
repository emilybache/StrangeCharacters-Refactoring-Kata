import os
from pathlib import Path

import pytest


@pytest.fixture
def strange_characters_filename():
    paths = ["strange_characters.json",
             "../strange_characters.json",
             Path(os.path.dirname(os.path.realpath(__file__))) / "strange_characters.json",
             ]
    for path in paths:
        if os.path.exists(path):
            return path
