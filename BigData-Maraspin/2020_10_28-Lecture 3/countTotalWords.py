import pyspark

# Creates context - local implies localhost is used, * is to enable parallelism on all available cores
sc = pyspark.SparkContext('local[*]')

txt = sc.textFile('file:////srv/apps/its-bigdata-2020/samples/artwar.txt')

counts = txt.flatMap(lambda line: line.split(" ")) \
             .map(lambda word: ("parola", 1)) \
             .reduceByKey(lambda a,b: a + b)
             
parola = counts.collect()

print(parola)