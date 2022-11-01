using AbstractTrees
using Gumbo, Cascadia

function getTable(doc)
    s=Selector("#tab1")
    eachmatch(s,doc.root)
end

function getTableRows(table)
    eachmatch(Selector(".on_schedule_row"), table)
end


file = open("schedule.html")
doc = parsehtml(read(file, String))
table = getTable(doc)
rows = getTableRows(table[1])

for row in rows
    date = strip(nodeText(eachmatch(Selector("h3"), row)[1]))
    times = eachmatch(Selector(".time_block"), row)
    names = eachmatch(Selector(".name_block"), row)
    println(split(date," ")[1])
    
    for i in 1:length(names)
        body = split(strip(nodeText(names[i])), ";")
        name = body[1]
        other = strip(join(body[2:length(body)], ";"))
        time = split(strip(nodeText(times[i])), "–")
        start_time = time[1]
        end_time = time[2]
        println(name)
        println("$start_time - $end_time")
        println(other)
    end
    println()
end
