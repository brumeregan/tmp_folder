% rebase('base.tpl')
<h1>Годовой план на продукті по заказам</h1>
{{current_year}}
<table>
    <thead>
        <th>#</th>
        <th>Product name</th>
        <th>Amount</th>
    </thead>
    <tbody>
        %for item in items:
            <tr>
                <td>{{ item['id'] }}</td>
                <td>{{ item['product_name'] }}</td>
                <td>{{ item['amount'] }}</td>
            </tr>
        %end
    </tbody>
</table>

