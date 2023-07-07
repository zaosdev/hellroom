mationen zum Einrichten der Umgebung verwenden, bevor CMake aufgerufen wird.",
										"enum": [
											"set",
											"external"
										]
									}
								},
								"additionalProperties": false
							}
						]
					},
					"toolset": {
						"anyOf": [
							{
								"type": "string",
								"description": "Eine optionale Zeichenfolge, die das Toolset für Generatoren repräsentiert, die es unterstützen."
							},
							{
								"type": "object",
								"description": "Ein optionales Objekt, das das Toolset für Generatoren repräsentiert, die es unterstützen.",
								"properties": {
									"value": {
										"type": "string",
										"description": "Eine optionale Zeichenfolge, die den Wert repräsentiert."
									},
									"strategy": {
										"type": "string",
										"description": "Eine optionale Zeichenfolge mit Anweisungen zur Verarbeitung des Felds für CMake. Gültige Werte: \"set\": Der entsprechende Wert wird festgelegt. Dies führt zu einem Fehler für Generatoren, die das entsprechende Feld nicht unterstützen. \"external\": Der Wert wird nicht festgelegt, selbst wenn er vom Generator unterstützt wird. Dies ist nützlich, wenn z. B. eine Voreinstellung den Ninja-Generator verwendet und eine IDE die Informationen zur Einrichtung der Visual C++-Umgebung aus den Feldern \"architecture\" und \"toolset\" bezieht. I