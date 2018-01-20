% rebase('base.tpl')
<h1>Таблица выпускаемых товаров с кодом и ценой</h1>
<table>
    <thead>
        <th>ID</th>
        <th>Product name</th>
        <th>Price</th>
    </thead>
    <tbody>
        %for item in items:
            <tr>
                <td>{{ item['id'] }}</td>
                <td>{{ item['product_name'] }}</td>
                <td>{{ item['price'] }}</td>
            </tr>
        %end
    </tbody>
</table>

