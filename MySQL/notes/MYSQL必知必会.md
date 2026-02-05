```mysql
-- 本测试是在MYSQL必知必会的环境下进行测试
use study;
-- 这种查询并未对返回的数据进行排序，返回的数据可能在某一种情况下是没有意义的

-- ------------------------------- 第四章 检索数据----------------------------------------
-- 检索所有的列
select * from vendors;
-- 检索单个列
select vend_name from vendors;
-- 将该表中指定的多列输出
select vend_name,vend_id,vend_city
from vendors;
-- 利用关键子distinct来输出不同的行的信息，该关键仅仅作用于关键字后面的列
select distinct order_num from orderitems;

-- 限制输出的结果,利用关键字limit,将输出结果的个数限制在5个以内
select order_num from orderitems limit 5;
-- 如果limit关键字后面是两个数字的话，limit n, m，我们就会返回从第n行开始的m行,注意在表中，第一行的行号是0，所以说limit 0, 4
-- 是返回从第一行开始数一共4行
select cust_id from customers limit 0,4;


-- 输出结果为暂时修改表的名字为下面这几种
select cust_id      as ci,
       cust_name    as cn,
       cust_address as ca,
       cust_city    as cc,
       cust_state   as cs,
       cust_zip     as cz,
       cust_country as c,
       cust_contact as cc2,
       cust_email   as ce
from customers;


-- 该方法是限制表的名字,后面的场景可能会使用到
select orders.order_num from orders;
select orderitems.order_num from orderitems;

-- ---------------------------------第五章 排序数据---------------------------------------------------
-- 该章节引进了SQL字句，其实就是SQL语句的组成部分，这里我们引进了新的字句 ORDER BY，可以按照某一个关键字进行排序
select orderitems.order_num from orderitems order by order_num;

-- 我们比较的关键字可以从表格中的某一列的名字中选取
select orderitems.order_num,orderitems.order_item,orderitems.quantity from orderitems order by quantity;

-- 如果是按照多列来进行排序的话，我们优先比较第一个关键字，即order_num， 然后比较 o'r'd'r'r
select order_num, order_item, quantity
from orderitems
order by order_num, order_item, quantity;

-- 如果我们需要按照降序进行排序的话，我们需要指明关键字desc, 即descend,降序
-- 下面的例子是将order_num该列按照降序排列，其他各列依旧按照升序进行排列
select order_num, order_item, quantity
from orderitems
order by order_num desc, order_item, quantity;


-- ------------------------------------------第六章 过滤数据-----------------------------------------------
-- 我们可以使用where子句对我们输出结果进行筛选和过滤
-- 我们指定条件来限制
select *
from orderitems
where quantity < 5;

-- 我们也可以进行范围性的筛选，在我们指定的范围内去过滤数据
select *
from orderitems
where quantity between 2 and 5;

-- -----------------------------------------第七章 数据过滤------------------------------------------------
-- 我们上面所列的仅仅是单一数据，我们还可以设置多个条件进行过滤，我们需要使用到AND操作符或者OR操作符, 这个和高级语言中的逻辑
-- 是互通的, 不过我们需要注意其优先级，使用括号来使得关键字的优先级更高
-- 我们经常使用到的关键字主要有以下几种：
-- AND OR NOT IN

-- -----------------------------------------第八章 使用通配符进行过滤----------------------------------------
-- 首先介绍的是LIKE操作符，LIKE指示MYSQL，后面跟的搜索模式利用通配符而不是直接相等匹配进行比较

-- 比如说我们经常使用的是百分号%：
-- 我们下面这样写是不会区分大小写的，我们需要使用关键字binary

select prod_id, prod_name
from products
where prod_name like 'jet%';

select prod_id, prod_name
from products
where prod_name like binary 'jet%';

-- 上面所使用的通配符是%是可以匹配多个字符的，我们可以使用另一种通配符 ‘-’ 该种通配符只能匹配单个字符

select prod_id, prod_name
from products
where prod_name like '_ ton anvil';


-- 在上面的语句中可以看到通配符的强大，但是是由代价的，通配符的处理时间比前面的搜索时间都要长
-- 所以说，不要过度的使用通配符，如果其他操作符可以达到相同的目的的话，应该使用其他的操作符
-- 不要将通配符放在搜索模式的开始处，将其放在搜索模式的开始处是最慢的

-- ------------------------------------第九章 使用正则表达式进行搜索----------------------------------------------
-- ------------------------------------第十章 创建计算字段------------------------------------------------------
-- 一般来说，我们存储在数据库中的数据一般都不是我们所需要的数据，一般来讲的话，我们需要对表中的列进行组合之后输出
-- 这就需要用到我们所谓的计算字段和拼接字段的功能，该部分一般都是在select语句之后创建并完成的

-- 比如说拼接字段，MYSQL与其他的DBMS不同，MYSQL一般是使用Concat()函数来实现拼接字段的功能的，比如：
select CONCAT(vend_name, '(', vend_city, ')')
from vendors
order by vend_name;

-- 另外我们如果想要删除表中数据中的右边或者左边的空格，我们可以使用RTrim()函数或者LTrim()函数或者Trim()函数（删除两边的空格）
select CONCAT(RTRIM(vend_name), '(', RTRIM(vend_country), ')')
FROM vendors
ORDER BY vend_name;

-- 上面我们已经很好的处理了数据将指定列给拼接到了一起，但是现在新合成的数据并没有名字，这样就会导致客户端无法引用得到的新的数据
-- 所以我们引入了别名，我们可以为新合成的数据起一个别名，然后客户端就可以引用新得到的数据
select CONCAT(RTRIM(vend_name), '(', RTRIM(vend_country), ')') as vend_title
FROM vendors
ORDER BY vend_name;

-- 我们也可以执行算术运算，执行最基本的+ - * /

select prod_id,
       quantity,
       item_price,
       quantity * item_price AS expanded_price
from orderitems
where order_num = 20005;

select now();

-- 以上部分是我们如何进一步对多种数据进行拼接和组合，接下来我们来讨论如何使用数据处理函数
-- ----------------------------------------第11章 使用数据处理函数------------------------------------------------
-- 数据库中的函数有很多种:
-- 用于处理文本的函数，将文本全部变成大写，或者删除指定字符；
-- 用于数值计算的函数;
-- 用于处理日期的函数;
-- 返回当前数据库的特殊信息，比如说用户登录信息等等;

-- ----------------------------------------第12章 汇总数据-------------------------------------------------------
-- 我们可以将其总结为，就是我们想要获得数据的特征，而不是具体的数据，这个时候就需要我们的来汇总数据
-- SQL聚集函数可以用来汇总数据。这可以使得我们对行进行计数和与平均值，获得最大和最小值而不需要检索所有的数据

-- ----------------------------------------第13章 分组数据-------------------------------------------------------
-- 我们现在有一个数据集，里面存储的是所有的商品，每一个条目都包含了商品的供货商，然后如果我们想要获得指定供货商供应的商品的数量的话
select count(*) as num_prods
from products
where vend_id = 1003;

-- 这个时候如果我们想要获得所有供应商关于此处的信息, 我们就得需要用到分组, 即我们以供应商为单位进行分组，然后分别在各个分组中计算相
-- 的数据
select vend_id, count(*) as num_prods
from products
group by vend_id;

-- 以上部分是我们通过分组得到各组的数据，我们还可以进行进一步的的限制，使用HAVING关键字来进行过滤
select vend_id, count(*) as num_prods
from products
group by vend_id
having count(*) >= 6;

-- ----------------------------------------第14章 利用子查询-------------------------------------------------------
-- 嵌套在查询中的查询，即使多个查询的嵌套
select cust_id
from orders
where order_num in (select order_num
                    from orderitems
                    where prod_id = 'TNT2');

-- ----------------------------------------第15章 联结表----------------------------------------------------------
-- 联结表中实际上就是我们通过主键和外键将两张表或者更多表联结起来，这样的话，我们就不需要将两张表中的数据存储在一张表中
-- 这样利用主键和外键将多张表联结起来不仅仅可以节省空间，并且还可以节省时间

-- 与此同时，我们将数据分散到多个表中是有一定的代价的
-- 比如说，我们怎么将原本属于一个表的数据检索出来，答案就是使用联结，就是一种机制，我们可以在select语句中关联不同的表。
-- 使用特殊的语法，可以联结多个表返回一组输出，联结在运行的时候关联表中正确的行

-- 如何创建联结
select vend_name, prod_name, prod_price
from vendors, products
where vendors.vend_id = products.vend_id
order by vend_name, prod_name;

-- -----------------------------------------第22章 使用视图-------------------------------------------------------
-- 像第15章的内容一样，如果我们每一次检索数据的时候, 都这样输入难免会导致极大的麻烦, 所以说我们引入了更高级的视图, 我们可以利用视图大大
-- 大大的简化我们的输入

-- 未简化之前的输入
select cust_name, cust_contact
from customers,orders, orderitems
where customers.cust_id = orders.cust_id
    AND orderitems.order_num = orders.order_num
    AND prod_id = 'TNT2';

-- 该检索是用来检索订购了某一个特定产品的客户，任何需要这个数据的人都必须理解相关表的结构
-- 然后我们看这一串代码的时候，是很难看懂的
-- 首先我们将订单orders中的数据和顾客customers中的数据联结起来，即输出条件是如果订单中的顾客名字是和顾客表中的名字是相等的再进入下一步
-- 接着我们将订单orders中的数据和orderitems中的数据联结起来，就是如果物品的名字在订单表中的话，我们就进入下一步
-- 最后输出商品号为TNT2的相关行

-- 假如我们可以将整个查询包包装成一个名为productcustomers的虚拟表，那我们就可以像下面这样轻松的检索出数据；
select cust_name, cust_contact
from productcustomers
where prod_id = 'TNT2';

-- 我们使用表之后，可以方便很多，比如说我们可以重用SQL语句
-- 简化复杂的SQL操作，在编写查询之后，我们就可以方便的重用它而不必知道他的基本查询细节

-- 创建视图，视图其实就是通过select语句先将多个表中的数据联结起来，形成一个虚拟表
-- 然后视图的属性和表的属性差不多都是一样的

-- 创建视图productcustomers, 该虚拟表中的关键字有cust_name, cust_contact, prod_id
create view productcustomers as
select cust_name, cust_contact, prod_id
from customers, orders, orderitems

where customers.cust_id = orders.cust_id
    AND orderitems.order_num = orders.order_num;

select * from productcustomers;

-- 我们还可以利用视图重新格式化检索出的数据，就是利用拼接字段，我们可以将多个表格的数据先输出并进行格式转换
-- 将其转换为我们相应的格式然后放虚拟表中

select CONCAT(RTRIM(vend_name), '(', RTRIM(vend_country), ')') AS VEND_TITLE
FROM vendors
ORDER BY  vend_name;

CREATE VIEW vendorlocations as
select CONCAT(RTRIM(vend_name), '(', RTRIM(vend_country), ')') AS VEND_TITLE
FROM vendors
ORDER BY  vend_name;


select *
from vendorlocations;
```

