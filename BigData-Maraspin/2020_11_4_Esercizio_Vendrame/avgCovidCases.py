import pyspark

es_conf = {
    "es.nodes" : 'localhost', # master node
    "es.port" : '9200',
    "es.resource" : 'covid/_doc',
    "es.input.json" : "yes",
}

# Creates context - local implies localhost is used, * is to enable parallelism on all available cores
sc = pyspark.SparkContext('local[*]')

def estrai(record):
    print(record[1]["bodyTemperature"])
    return (record[1]["covidPositive"],{"bodyTemperature": record[1]["bodyTemperature"],"average" : record[1]["bodyTemperature"], "people" : 1})
    
def unisci(a, b):
    return { 
             "bodyTemperature": a["bodyTemperature"] + b["bodyTemperature"],
             "people": a["people"] + b["people"],
             "average": ((a["bodyTemperature"] + b["bodyTemperature"]) / (a["people"] + b["people"])) 
           }

# Reading stuff from Elasticsearch
dd = sc.newAPIHadoopRDD("org.elasticsearch.hadoop.mr.EsInputFormat",
                             "org.apache.hadoop.io.NullWritable",
                             "org.elasticsearch.hadoop.mr.LinkedMapWritable",
                            conf=es_conf)

# useful for debugging
print(dd.first())

tempCol = dd.map(estrai)

print(tempCol.collect())

cleanCol = tempCol.reduceByKey(unisci)

results = cleanCol.map(lambda item: { 
    'covidPositive': item[0],
    'average': item[1]["average"]
})

print(results.collect())

cleanCol.saveAsTextFile("./covidResult");