import json
from functools import reduce
import pyspark

sc = pyspark.SparkContext('local[*]')
json = sc.textFile('file:////srv/apps/its-bigdata-2020/samples/sales.json')

print(json.collect())
#country_record = (list(map(lambda record: (record["value"]), data)))
#print(country_record)

#country_result = reduce(lambda val1, val2: val1 + val2, sorted(country_record))

#print(country_result)