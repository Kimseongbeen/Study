task
```
{
  "name": "업무 등록",
  "nodes": [
    {
      "parameters": {
        "model": "gpt-4o-2024-08-06",
        "options": {
          "temperature": 0,
          "topP": 0.1
        }
      },
      "id": "690a5c06-6d8d-4adf-9464-6f7298f0da5a",
      "name": "OpenAI Chat Model2",
      "type": "@n8n/n8n-nodes-langchain.lmChatOpenAi",
      "typeVersion": 1,
      "position": [
        -420,
        880
      ],
      "credentials": {
        "openAiApi": {
          "id": "Wm5Lj6YAVw0t94P3",
          "name": "OpenAi account 2"
        }
      }
    },
    {
      "parameters": {
        "project": {
          "__rl": true,
          "value": "2343016222",
          "mode": "list",
          "cachedResultName": "할일"
        },
        "labels": [
          "2176301992"
        ],
        "content": "={{ $json.task_name }}",
        "options": {
          "description": "=내용: {{ $json.description }}\n분류: {{ $json.category }}\n담당자: {{ $json.assignee }}",
          "dueDateTime": "={{ $json.due_date }}",
          "priority": "={{5- $json.priority}}"
        }
      },
      "id": "cedcb286-9f8b-4c9e-8a88-ae6b55dc52bc",
      "name": "performance",
      "type": "n8n-nodes-base.todoist",
      "typeVersion": 1,
      "position": [
        380,
        920
      ],
      "credentials": {
        "todoistApi": {
          "id": "sny8iTj9SB44fadp",
          "name": "Todoist account"
        }
      }
    },
    {
      "parameters": {
        "jsCode": "const items = $input.all()[0].json.output.items;\nconst transformedItems = items.map(item => {\n  return {\n    json: item\n  };\n});\n\nreturn transformedItems;"
      },
      "id": "94146138-74b7-4336-b893-952e8134eda3",
      "name": "Code",
      "type": "n8n-nodes-base.code",
      "typeVersion": 2,
      "position": [
        -120,
        700
      ],
      "alwaysOutputData": false
    },
    {
      "parameters": {
        "project": {
          "__rl": true,
          "value": "2343016222",
          "mode": "list",
          "cachedResultName": "할일"
        },
        "labels": [
          "2176301986"
        ],
        "content": "={{ $json.task_name }}",
        "options": {
          "description": "=내용: {{ $json.description }}\n분류: {{ $json.category }}\n담당자: {{ $json.assignee }}",
          "dueDateTime": "={{ $json.due_date }}",
          "priority": "={{5- $json.priority}}"
        }
      },
      "id": "fd05da74-cb0b-41af-a235-c83823f91bf2",
      "name": "security",
      "type": "n8n-nodes-base.todoist",
      "typeVersion": 1,
      "position": [
        380,
        600
      ],
      "credentials": {
        "todoistApi": {
          "id": "Eko2C0aDiQomGOae",
          "name": "Todoist account 2"
        }
      }
    },
    {
      "parameters": {
        "project": {
          "__rl": true,
          "value": "2343016222",
          "mode": "list",
          "cachedResultName": "할일"
        },
        "labels": [
          "2176301995"
        ],
        "content": "={{ $json.task_name }}",
        "options": {
          "description": "=내용: {{ $json.description }}\n분류: {{ $json.category }}\n담당자: {{ $json.assignee }}",
          "dueDateTime": "={{ $json.due_date }}",
          "priority": "={{5- $json.priority}}"
        }
      },
      "id": "8b282f13-6274-4fd7-99af-9f80e5e8d8d0",
      "name": "feature",
      "type": "n8n-nodes-base.todoist",
      "typeVersion": 1,
      "position": [
        380,
        1080
      ],
      "credentials": {
        "todoistApi": {
          "id": "sny8iTj9SB44fadp",
          "name": "Todoist account"
        }
      }
    },
    {
      "parameters": {
        "project": {
          "__rl": true,
          "value": "2343016222",
          "mode": "list",
          "cachedResultName": "할일"
        },
        "labels": [
          "2176301987"
        ],
        "content": "={{ $json.task_name }}",
        "options": {
          "description": "=내용: {{ $json.description }}\n분류: {{ $json.category }}\n담당자: {{ $json.assignee }}",
          "dueDateTime": "={{ $json.due_date }}",
          "priority": "={{5- $json.priority}}"
        }
      },
      "id": "2b3e7372-5a19-4e1e-842b-d44b1a991690",
      "name": "hardware",
      "type": "n8n-nodes-base.todoist",
      "typeVersion": 1,
      "position": [
        380,
        760
      ],
      "credentials": {
        "todoistApi": {
          "id": "sny8iTj9SB44fadp",
          "name": "Todoist account"
        }
      }
    },
    {
      "parameters": {
        "project": {
          "__rl": true,
          "value": "2343016222",
          "mode": "list",
          "cachedResultName": "할일"
        },
        "labels": [
          "2176301985"
        ],
        "content": "={{ $json.task_name }}",
        "options": {
          "description": "=내용: {{ $json.description }}\n분류: {{ $json.category }}\n담당자: {{ $json.assignee }}",
          "dueDateTime": "={{ $json.due_date }}",
          "priority": "={{5- $json.priority}}"
        }
      },
      "id": "7ce77523-c7e0-4086-a6fc-f39915288956",
      "name": "critical-bug",
      "type": "n8n-nodes-base.todoist",
      "typeVersion": 1,
      "position": [
        380,
        440
      ],
      "credentials": {
        "todoistApi": {
          "id": "Eko2C0aDiQomGOae",
          "name": "Todoist account 2"
        }
      }
    },
    {
      "parameters": {},
      "id": "9a578e9b-a70a-4c2b-893c-00625533c6a8",
      "name": "When clicking ‘Test workflow’",
      "type": "n8n-nodes-base.manualTrigger",
      "typeVersion": 1,
      "position": [
        -560,
        700
      ]
    },
    {
      "parameters": {
        "text": "=펌웨어 개발팀 일일 스크럼 회의록\n2024-11-06 (10:00-10:10)\n팀장: 오늘도 빠르게 진행하겠습니다. 김엔지니어님부터 시작할게요.\n김엔지니어: 네, 어제 저녁부터 MCU 과열 시 시스템 크래시 현상이 보고됐습니다. 온도 모니터링 인터럽트 핸들러에서 메모리 오버플로우가 의심되는 상황입니다. 오늘 중으로 핫픽스 배포하도록 하겠습니다.\n팀장: 네, 이건 최우선순위로 처리해주세요. 박개발님은 어떠신가요?\n박개발: 신규 센서 I2C 드라이버 구현이 현재 70% 정도 진행됐습니다. 기본적인 읽기/쓰기는 구현 완료했고, 이번 주까지 멀티바이트 통신 구현하는 것이 목표입니다.\n팀장: 좋습니다. 목요일까지 코드 리뷰 준비해주시고요. 이최적님?\n이최적: RTOS 태스크 스케줄링 최적화를 진행 중입니다. 목표는 메모리 사용량 20% 감소인데, 현재 분석 단계에 있습니다.\n팀장: 알겠습니다. 정보안님?\n정보안: OTA 업데이트 보안 강화 건 검토 중입니다. AES-256 암호화 적용을 고려하고 있는데, 이번 주 내로 최종 방식 결정하도록 하겠습니다.\n팀장: 네, 최기능님 마지막으로 부탁드립니다.\n최기능: 저전력 모드 구현을 다음 주부터 시작할 예정입니다. 현재는 요구사항 분석과 계획 수립 단계입니다.\n팀장: 알겠습니다. 추가로 박개발님 I2C 드라이버 문서화도 잊지 말아주시고, 다음 주 통합 테스트도 있으니 모두 준비 부탁드립니다. 더 논의할 사항 있으신가요?\n(전원 고개 젓는 중)\n팀장: 그럼 오늘 스크럼 미팅은 여기서 마치도록 하겠습니다. 김엔지니어님 크래시 이슈는 진행상황 수시로 공유해주세요.\n김엔지니어: 네, 알겠습니다.\n팀장: 수고하셨습니다.\n회의록 작성: 홍비서",
        "schemaType": "fromJson",
        "jsonSchemaExample": "{\n    \"items\": [\n        {\n            \"task_name\": \"작업1\",\n            \"description\": \"작업의 관련 내용\",\n            \"category\": \"카테고리\",\n            \"priority\": 1,\n            \"assignee\": \"담당자\",\n            \"due_date\": \"기한\"\n        },\n        {\n            \"task_name\": \"작업2\",\n            \"description\": \"작업의 관련 내용\",\n            \"category\": \"카테고리\",\n            \"priority\": 3,\n            \"assignee\": \"담당자\",\n            \"due_date\": \"기한\"\n        },\n        {\n            \"task_name\": \"작업3\",\n            \"description\": \"작업의 관련 내용\",\n            \"category\": \"카테고리\",\n            \"priority\": 3,\n            \"assignee\": \"담당자\",\n            \"due_date\": \"기한\"\n        },\n        {\n            \"task_name\": \"작업4\",\n            \"description\": \"작업의 관련 내용\",\n            \"category\": \"카테고리\",\n            \"priority\": 3,\n            \"assignee\": \"담당자\",\n            \"due_date\": \"기한\"\n        },\n        {\n            \"task_name\": \"작업6\",\n            \"description\": \"작업의 관련 내용\",\n            \"category\": \"카테고리\",\n            \"priority\": 4,\n            \"assignee\": \"담당자\",\n            \"due_date\": \"기한\"\n        },\n        {\n            \"task_name\": \"작업8\",\n            \"description\": \"작업의 관련 내용\",\n            \"category\": \"카테고리\",\n            \"priority\": 3,\n            \"assignee\": \"담당자\",\n            \"due_date\": \"기한\"\n        },\n        {\n            \"task_name\": \"작업11\",\n            \"description\": \"작업의 관련 내용\",\n            \"category\": \"카테고리\",\n            \"priority\": 3,\n            \"assignee\": \"담당자\",\n            \"due_date\": \"기한\"\n        },\n        {\n            \"task_name\": \"작업12\",\n            \"description\": \"작업의 관련 내용\",\n            \"category\": \"카테고리\",\n            \"priority\": 3,\n            \"assignee\": \"담당자\",\n            \"due_date\": \"기한\"\n        },\n        {\n            \"task_name\": \"작업15\",\n            \"description\": \"작업의 관련 내용\",\n            \"category\": \"카테고리\",\n            \"priority\": 3,\n            \"assignee\": \"담당자\",\n            \"due_date\": \"기한\"\n        }\n    ]\n}\n\n",
        "options": {
          "systemPromptTemplate": "=회의록 분석 가이드라인:\n1. 출력 형식\ntask_name = 작업의 이름\ndescription = 작업의 구체적인 내용\ncategory = critical-bug/security/hardware/performance/feature\npriority = 카테고리별 우선순위 숫자\nassignee = 담당자 이름 (선택)\ndue_date = 작업 기한 (선택)\n*내용은 한글로\n\n2. 우선순위 규칙\ncritical-bug = 1\nsecurity = 1 \nhardware = 2\nperformance = 3\nfeature = 4\n\n3. 추출 기준 \n- 모든 관련 작업을 찾아서 추출\n- assignee, due_date는 있는 경우만 포함\n\n4. 반환 형식\n단일 객체 내 items 배열로 모든 작업을 포함\n\n5. 작업 기한(due_date) 자동 할당 규칙:\n- critical-bug 카테고리: \"오늘 까지\"로 설정\n- security 카테고리: \"내일 까지\"로 설정\n- hardware 카테고리: \"다음 주 까지\"로 설정\n- performance 카테고리: \"다음 주 까지\"로 설정\n- feature 카테고리: \"2주 뒤 까지\"로 설정\n- 기타 모든 카테고리: 기본값 \"다음 주 까지\"로 설정\n* 명시된 기한이 있으면 해당 기한 우선\n* 시간은 설정된 값의  YYYY-MM-DD 형식에 시간을 포함한 ISO 8601 형식: 2024-11-06T12:00:00+09:00\n\n6. JSON 응답 형식 안내:\n* 예시는 단순 참고용이며, 실제 items 배열에는 발견된 모든 작업이 포함되어야 함"
        }
      },
      "id": "32fe567f-3001-453e-a1a1-8492881594dc",
      "name": "Information Extractor(요약)",
      "type": "@n8n/n8n-nodes-langchain.informationExtractor",
      "typeVersion": 1,
      "position": [
        -420,
        700
      ],
      "alwaysOutputData": false,
      "notesInFlow": false,
      "executeOnce": false
    },
    {
      "parameters": {
        "rules": {
          "values": [
            {
              "conditions": {
                "options": {
                  "caseSensitive": true,
                  "leftValue": "",
                  "typeValidation": "strict",
                  "version": 2
                },
                "conditions": [
                  {
                    "leftValue": "={{ $json.category }}",
                    "rightValue": "critical-bug",
                    "operator": {
                      "type": "string",
                      "operation": "equals"
                    }
                  }
                ],
                "combinator": "and"
              }
            },
            {
              "conditions": {
                "options": {
                  "caseSensitive": true,
                  "leftValue": "",
                  "typeValidation": "strict",
                  "version": 2
                },
                "conditions": [
                  {
                    "id": "13fcd914-fde1-434b-8761-8d6fce6c88b4",
                    "leftValue": "={{ $json.category }}",
                    "rightValue": "security",
                    "operator": {
                      "type": "string",
                      "operation": "equals",
                      "name": "filter.operator.equals"
                    }
                  }
                ],
                "combinator": "and"
              }
            },
            {
              "conditions": {
                "options": {
                  "caseSensitive": true,
                  "leftValue": "",
                  "typeValidation": "strict",
                  "version": 2
                },
                "conditions": [
                  {
                    "id": "e4711a63-6777-4745-b1df-fa1ea11d6c29",
                    "leftValue": "={{ $json.category }}",
                    "rightValue": "hardware",
                    "operator": {
                      "type": "string",
                      "operation": "equals",
                      "name": "filter.operator.equals"
                    }
                  }
                ],
                "combinator": "and"
              }
            },
            {
              "conditions": {
                "options": {
                  "caseSensitive": true,
                  "leftValue": "",
                  "typeValidation": "strict",
                  "version": 2
                },
                "conditions": [
                  {
                    "id": "927d5391-2b5b-4108-8fda-909ede8f5775",
                    "leftValue": "={{ $json.category }}",
                    "rightValue": "performance",
                    "operator": {
                      "type": "string",
                      "operation": "equals",
                      "name": "filter.operator.equals"
                    }
                  }
                ],
                "combinator": "and"
              }
            },
            {
              "conditions": {
                "options": {
                  "caseSensitive": true,
                  "leftValue": "",
                  "typeValidation": "strict",
                  "version": 2
                },
                "conditions": [
                  {
                    "id": "0fe571cd-59f4-40fe-9b5c-39a328e28102",
                    "leftValue": "={{ $json.category }}",
                    "rightValue": "feature",
                    "operator": {
                      "type": "string",
                      "operation": "equals",
                      "name": "filter.operator.equals"
                    }
                  }
                ],
                "combinator": "and"
              }
            }
          ]
        },
        "options": {}
      },
      "id": "996662c0-6262-4cc8-818c-294d13734879",
      "name": "Switch",
      "type": "n8n-nodes-base.switch",
      "typeVersion": 3.2,
      "position": [
        20,
        700
      ]
    }
  ],
  "pinData": {},
  "connections": {
    "OpenAI Chat Model2": {
      "ai_languageModel": [
        [
          {
            "node": "Information Extractor(요약)",
            "type": "ai_languageModel",
            "index": 0
          }
        ]
      ]
    },
    "Code": {
      "main": [
        [
          {
            "node": "Switch",
            "type": "main",
            "index": 0
          }
        ]
      ]
    },
    "When clicking ‘Test workflow’": {
      "main": [
        [
          {
            "node": "Information Extractor(요약)",
            "type": "main",
            "index": 0
          }
        ]
      ]
    },
    "Information Extractor(요약)": {
      "main": [
        [
          {
            "node": "Code",
            "type": "main",
            "index": 0
          }
        ]
      ]
    },
    "Switch": {
      "main": [
        [
          {
            "node": "critical-bug",
            "type": "main",
            "index": 0
          }
        ],
        [
          {
            "node": "security",
            "type": "main",
            "index": 0
          }
        ],
        [
          {
            "node": "hardware",
            "type": "main",
            "index": 0
          }
        ],
        [
          {
            "node": "performance",
            "type": "main",
            "index": 0
          }
        ],
        [
          {
            "node": "feature",
            "type": "main",
            "index": 0
          }
        ]
      ]
    }
  },
  "active": false,
  "settings": {
    "executionOrder": "v1"
  },
  "versionId": "84eb32a4-4a5a-48cd-bf55-944b1901c912",
  "meta": {
    "templateCredsSetupCompleted": true,
    "instanceId": "558d88703fb65b2d0e44613bc35916258b0f0bf983c5d4730c00c424b77ca36a"
  },
  "id": "h4xr5RzJlV3NLVKs",
  "tags": []
}
```