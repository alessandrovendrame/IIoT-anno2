import json
from functools import reduce

with open('sales.json') as f:
  data = json.load(f)

country_record = (list(map(lambda record: (record["value"]), data)))
print(country_record)

country_result = reduce(lambda val1, val2: val1 + val2, sorted(country_record))

print(country_result)
