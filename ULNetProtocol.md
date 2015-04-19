# Introduction #

Undersea Llamas clients and the Shredder server will communicate via a text network protocol. This ULNet protocol is single-line based, enabling simple readability.


# Details #

This protocol is implemented via one-line commands. Each command and its format is described below.

|Command|Arguments|Client/Server|Description|
|:------|:--------|:------------|:----------|
|ULGETLIST|none|Client->Server|Tells server to return list of active games|
|ULLISTBEGIN|none|Server->Client|Tells client to expect list of games|
|ULLISTITEM|gamenumber:exploredpercent:playercount|Server->Client|Tells client about a particular game|
|ULENDLIST|none|Server->Client|Tells client the list of games is over|
|ULCONNECT|gamenumber:username|Client->Server|Asks server to connect to the specified game|
|ULDENY|none|Either|General deny packet|
|ULGAMEJOINED|gamenumber|Server->Client|Tells client it's connected, and to expect data shortly.|
|ULWORLDBEGIN|none|Server->Client|Tells client to expect a ULWorld-format data stream.|
|ULWORLDEND|none|Server->Client|Tells client the ULWorld stream is over|
|ULSTATEBEGIN|none|Server->Client|Tells client to expect a ULState-format data stream.|
|ULSTATEEND|none|Server->Client|Tells client to expect a ULState-format data stream.|
|ULMOVE|llama:x:y|Either|Tells the other end that a llama was moved.|
|ULOPEN|llama:x:y:pesos:damage|Tells the other end that a chest was opened|
|ULREQUESTQUIT|llama|Client->Server|Requests that the server disconnect the client.|
|ULDISCONNECT|llama|Server->Client|Tells the clients that `llama` disconnected.|
|ULTICK|ticknumber|Server->Client|Ticks the game on the client side.|