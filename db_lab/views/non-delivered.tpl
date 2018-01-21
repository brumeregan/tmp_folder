% rebase('base.tpl')
<h1>Таблица невыполненных обязательств за {{current_year}}</h1>
<table>
    <thead>
        <th>Order #</th>
        <th>Consumer name</th>
        <th>Product name</th>
        <th>Amount of product to deliver</th>
    </thead>
    <tbody>
        %for i, item in enumerate(items):
            <tr>
                <td>{{ item['order_id'] }}</td>
                <td>{{item['company_name']}}</td>
                <td><b>{{item['product_name']}}</b>,</td>
                <td>{{ item['amount_left']}}</td>
            </tr>
        %end
    </tbody>
</table>