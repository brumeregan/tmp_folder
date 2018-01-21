% rebase('base.tpl')
<h1>Таблица заказов</h1>
<table>
    <thead>
        <th>#order</th>
        <th>Product name</th>
        <th>amount</th>
        <th>consumer</th>
        <th>delivery date</th>
    </thead>
    <tbody>
        %for item in items:
            <tr>
                <td>{{ item['id'] }}</td>
                <td>{{ item['product_name'] }}</td>
                <td>{{ item['amount'] }}</td>
                <td>{{ item['company_name'] }}</td>
                <td>{{ item['delivery_date'] }}</td>
            </tr>
        %end
    </tbody>
</table>

<form action="/orders" method="post">
    <label>
        Select product
        <select name="product_id">
            %for prod in products:
                <option value={{prod['id']}}>{{prod['product_name']}}</option>
            %end
        </select>
    </label>
    <div>
        <label>
            Amount:
            <input type="number" value="" name="amount">
        </label>
    </div>
    <div>
        <label>Delivery date:</label>
        <input type="date" name="delivery_date">
    </div>
    <div>
        <label>
            Consumer:
            <select name="consumer_id">
                %for consumer in consumers:
                    <option value={{consumer['id']}}>{{consumer['company_name']}}</option>
                %end
            </select>
        </label>
    </div>
    <button>Submit</button>
</form>
