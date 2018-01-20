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
    c = db.execute('SELECT * FROM order_list')
    items = c.fetchall()
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

    print(delivery_date)

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
                       'GROUP BY product.product_name '
                       'ORDER BY product.id'.format(current_month=current_month)).fetchall()

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
    items = db.execute('SELECT product.id, product.product_name as product_name, '
                       'order_list.id, order_list.product_code, accounting.order_code, '
                       'accounting.issued_date as issued_date, '
                       'accounting.amount as amount, '
                       'consumer.company_name as company_name, consumer.id '
                       'FROM product, order_list, accounting, consumer '
                       'WHERE order_list.id = accounting.order_code '
                       'AND consumer.id = order_list.consumer_code '
                       'AND order_list.product_code = product.id').fetchall()

    return template('delivered', items=items)

# TODO add post request to add delivered order
@route('/delivered', method='POST')
def delivered_products(db):
    # product_code = request.forms.get('product_id')
    # amount = request.forms.get('amount')
    # delivery_date = request.forms.get('delivery_date')
    #
    # consumer_code = request.forms.get('consumer_id')
    #
    # print(delivery_date)
    #
    # db.execute('INSERT INTO order_list (product_code, amount, delivery_date, consumer_code) '
    #            'VALUES ({product_code}, {amount}, "{date}", {consumer})'.
    #            format(product_code=product_code, amount=amount, date=delivery_date, consumer=consumer_code))

    redirect('/delivered')

# annual
@route('/non-delivered')
def non_delivered_products(db):

    items = db.execute('select order_list.id as order_id, order_list.product_code, '
                       'order_list.consumer_code, '
                       'consumer.id, '
                       'consumer.company_name as company_name, '
                       'consumer.address as company_address, '
                       'product.id, '
                       'product.product_name as product_name, '
                       'ifnull(order_list.amount - accounting.amount, order_list.amount) as amount_left, '
                       'order_list.id '
                       'FROM order_list LEFT OUTER JOIN accounting on order_list.id = accounting.order_code, '
                       'consumer, product '
                       'WHERE order_list.consumer_code = consumer.id AND amount_left > 0 '
                       'AND order_list.product_code = product.id '
                       'GROUP BY order_list.id').fetchall()
    for i in items:
        print(dict(i))

    return template('non-delivered', items=items)


# DOublicated to delivered!!! TODO remove after checked
# @route('/accounting')
# def accounting(db):
#     items = db.execute('SELECT accounting.order_code as order_code, '
#                        'accounting.order_code as order_code, '
#                        'accounting.amount as amount_send, '
#                        'product.product_name as product_name, '
#                        'product.id, '
#                        'order_list.id, '
#                        'order_list.product_code, '
#                        'accounting.issued_date as issued_date '
#                        'from accounting, product, order_list '
#                        'WHERE accounting.order_code = order_list.id '
#                        'AND order_list.product_code = product.id').fetchall()
#
#     return template('accounting', items=items)
#
#
# @route('/accounting', method='POST')
# def accounting(db):
#     return template('accounting')

run(host='localhost', port=8080, debug=True, reloader=True)
