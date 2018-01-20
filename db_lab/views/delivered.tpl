% rebase('base.tpl')
<h1>This is delivered products</h1>
<form method="post">
    <select name="month">
        <option value="01">January</option>
        <option value="02">February</option>
        <option value="03">March</option>
        <option value="04">April</option>
        <option value="05">May</option>
        <option value="06">June</option>
        <option value="07">July</option>
        <option value="08">August</option>
        <option value="09">September</option>
        <option value="10">October</option>
        <option value="11">November</option>
        <option value="12">December</option>
    </select>
    <button>Submit</button>
</form>


<table>
    <thead>
        <th>#</th>
        <th>Product</th>
        <th>Amount</th>
        <th>Consumer</th>
        <th>Date</th>
    </thead>
    <tbody>
        %for i, item in enumerate(items):
            <tr>
                <td>{{i}}</td>
                <td>{{item['product_name']}}</td>
                <td>{{item['amount']}}</td>
                <td><b>{{item['company_name']}}</b>,</td>
                <td>{{ item['issued_date']}}</td>
            </tr>
        %end
    </tbody>
</table>