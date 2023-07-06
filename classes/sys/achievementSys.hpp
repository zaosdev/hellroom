properties": {},
						"additionalProperties": {
							"anyOf": [
								{
									"type": "null",
									"description": "Establecer una variable en NULL hace que no se defina, aunque se haya heredado un valor de otro preestablecido."
								},
								{
									"type": "string",
									"description": "Cadena que representa el valor de la variable."
								}
							]
						},
						"propertyNames": {
							"pattern": "^.+$"
						}
					},
					"configuration": {
						"type": "string",
						"description": "Cadena opcional. Equivale a pasar --build-config en la línea de comandos."
					},
					"overwriteConfigurationFile": {
						"type": "array",
						"description":