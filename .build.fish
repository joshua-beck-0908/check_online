#!/usr/bin/fish
pip freeze > requirements.txt
and python3 -m build
and python3 -m pip install --upgrade --target $PROJECT_DIR/_modules/py ./dist/*.whl
