from bottle import route, run, template, install, request, redirect
from bottle_sqlite import SQLitePlugin
from _datetime import datetime

install(SQLitePlugin(dbfile='db.sqlite3'))


@route('/')
def index():
    return template('index')

@route('/products')
def products(db):
    c = db.execute('SELECT * FROM product')
    row = c.fetchall()
    return template('products', items=row)

@route('/consumers')
def consumers(db):
    c = db.execute('SELECT * FROM consumer')
    row = c.fetchall()
    return template('consumers', items=row)

@route('/orders', method='GET')
def orders(db):
    items = db.execute('SELECT order_list.id, '
                       'order_list.amount as amount, '
                       'product.product_name as product_name, '
                       'consumer.company_name as company_name, '
                       'order_list.delivery_date as delivery_date '
                       'FROM order_list, product, consumer '
                       'WHERE order_list.product_code = product.id '
                       'AND order_list.consumer_code = consumer.id '
                       'ORDER BY order_list.id')

    consumers = db.execute('SELECT id, company_name FROM consumer')
    consumers_names = consumers.fetchall();
    products_db = db.execute('SELECT id, product_name FROM product')
    products = products_db.fetchall()

    return template('orders', items=items, consumers=consumers_names, products=products)

@route('/orders', method='POST')
def new_order(db):
    product_code = request.forms.get('product_id')
    amount = request.forms.get('amount')
    delivery_date = request.forms.get('delivery_date')
    consumer_code = request.forms.get('consumer_id')
    db.execute('INSERT INTO order_list (product_code, amount, delivery_date, consumer_code) '
               'VALUES ({product_code}, {amount}, "{date}", {consumer})'.
               format(product_code=product_code, amount=amount, date=delivery_date, consumer=consumer_code))

    redirect('/orders')

@route('/plan')
def plan():
    return template('plan')

@route('/plan-orders')
def plan_annual(db):
    current_year = '%04d' % datetime.now().year
    
    plan = db.execute('SELECT product.id as id,'
                      ' product.product_name as product_name,'
                      ' SUM(order_list.amount) as amount from product, order_list '
                      'WHERE order_list.product_code = product.id '
                      'and strftime("%Y", delivery_date) = "{current_year}" '
                      'GROUP BY product.product_name '
                      'ORDER BY product.id'.format(current_year=current_year)).fetchall()

    return template('plan-orders', items=plan, current_year=current_year)


#Єто план месяца по каждому товару
@route('/plan-monthly', method='GET')
def plan_monthly(db):
    current_year = '%04d' % datetime.now().year
    selected_month = request.query.get('selected_month')
    if(selected_month is not None):
        current_month = selected_month
    else:
        current_month = '%02d' % datetime.now().month

    items = db.execute('SELECT product.id, '
                       'product.product_name as product_name, '
                       'SUM(order_list.amount) as amount '
                       'FROM product, order_list '
                       'WHERE order_list.product_code = product.id '
                       'AND strftime("%m", delivery_date) = "{current_month}" '
                       'AND strftime("%Y", delivery_date) = "{year}" '
                       'GROUP BY product.product_name '
                       'ORDER BY product.id'.format(current_month=current_month, year=current_year)).fetchall()

    return template('plan-monthly', items=items, month=current_month)

#TODO
@route('/plan-order-monthly')
def order_monthly(db):
    selected_month = request.query.get('selected_month')
    if (selected_month is not None):
        current_month = selected_month
    else:
        current_month = '%02d' % datetime.now().month

    items = db.execute('SELECT product.id, '
                      'product.product_name as product_name, '
                      'SUM(order_list.amount) as amount, '
                      'order_list.consumer_code as consumer_code, '
                      'consumer.id, '
                      'consumer.company_name as consumer_name, '
                      'consumer.address as consumer_address '
                      'FROM product, order_list, consumer '
                      'WHERE order_list.product_code = product.id '
                      'AND consumer_code = consumer.id '
                      'AND strftime("%m", delivery_date) = "{current_month}" '
                      'GROUP BY product.product_name '
                      'ORDER BY product.id'.format(current_month=current_month)).fetchall()

    return template('plan-order-monthly', items=items, month=current_month)


@route('/delivered')
def delivered_products(db):
    selected_month = request.query.get('selected_month')
    if (selected_month is not None):
        current_month = selected_month

    #TODO Do we need filter by month?

    items = db.execute('SELECT product.id, product.product_name as product_name, '
                       'order_list.id, order_list.product_code, accounting.order_code, '
                       'accounting.issued_date as issued_date, '
                       'accounting.amount as amount, '
                       'consumer.company_name as company_name, consumer.id '
                       'FROM product, order_list, accounting, consumer '
                       'WHERE order_list.id = accounting.order_code '
                       'AND consumer.id = order_list.consumer_code '
                       'AND order_list.product_code = product.id').fetchall()

    orders = db.execute('SELECT order_list.id from order_list').fetchall()

    return template('delivered', items=items, orders=orders)

# TODO add post request to add delivered order
@route('/delivered', method='POST')
def delivered_products(db):
    order_id = request.forms.get('delivered_order')
    delivered_amount = request.forms.get('delivered_amount')
    delivered_date = request.forms.get('delivered_date')

    db.execute('INSERT INTO accounting (order_code, amount, issued_date) '
               'VALUES ({order_id}, {delivered_amount}, "{delivered_date}")'
               .format(order_id=order_id, delivered_amount=delivered_amount, delivered_date=delivered_date))
    redirect('/delivered')

# annual
@route('/non-delivered')
def non_delivered_products(db):
    current_year = '%04d' % datetime.now().year

    items = db.execute('select order_list.id as order_id, order_list.product_code, '
                       'order_list.consumer_code, '
                       'consumer.id, '
                       'consumer.company_name as company_name, '
                       'consumer.address as company_address, '
                       'product.id, order_list.delivery_date, '
                       'product.product_name as product_name, '
                       'ifnull(order_list.amount - accounting.amount, order_list.amount) as amount_left, '
                       'order_list.id '
                       'FROM order_list LEFT OUTER JOIN accounting on order_list.id = accounting.order_code, '
                       'consumer, product '
                       'WHERE order_list.consumer_code = consumer.id '
                       'AND strftime("%Y", order_list.delivery_date) = "{current_year}" '
                       'AND order_list.product_code = product.id '
                       'GROUP BY order_list.id HAVING amount_left > 0'.format(current_year=current_year)).fetchall()
    for i in items:
        print(dict(i))

    return template('non-delivered', items=items, current_year=current_year)


run(host='localhost', port=8080, debug=True, reloader=True)
